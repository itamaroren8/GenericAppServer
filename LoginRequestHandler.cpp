//
// Created by itamar on 7/12/26.
//

#include "LoginRequestHandler.h"

#include <stdexcept>
#include <utility>

#include "CONSTANTS.h"
#include "JsonDeserializer.h"
#include "JsonSerializer.h"
#include "LoggedUser.h"
#include "Requests.h"

LoginRequestHandler::LoginRequestHandler(IDatabase *db, std::vector<LoggedUser>& loggedUsers) : _db(db), _loggedUsers(loggedUsers) {}

/*
 * Serializes a response with the corresponding serializer.
 * INPUT: response: IResponse.
 * OUTPUT: std::vector<char>.
 */
std::vector<char> LoginRequestHandler::serializeResponse(const IResponse & response) {
    return JsonSerializer::serializeLoginResponse(response);
}

/*
 * Deserializes a request buffer with the corresponding deserializer.
 * INPUT: buffer: std::vector<char>.
 * OUTPUT: IRequest* (Uses polymorphism to send the correct type of request).
 */
IRequest *LoginRequestHandler::deserializeRequest(const std::vector<char> & buffer) {
    return JsonDeserializer::deserializeLoginRequest(buffer);
}

/*
 * Handles a client request (Login).
 * INPUT: request: LoginRequest*.
 * OUTPUT: true for success. false for failure. std::runtime_error for errors.
 */
IResult LoginRequestHandler::handleRequest(IRequest* request) {
    switch (request->_code) {
        case (Login): {
            const auto loginRequest = dynamic_cast<LoginRequest*>(request);
            if (!loginRequest) return {{PROTOCOL_FAILURE, "Request type is invalid!"}, this};

            try {
                bool result = login(loginRequest->_username, loginRequest->_password);
                if (result)
                    return {{PROTOCOL_SUCCESS}, this}; // TODO: change to a new request handler that will replace the login one.

                return {{PROTOCOL_FAILURE, "Couldn't verify user! Check user information and try again!"}, this};
            }
            catch (std::runtime_error& e) {
                return {{PROTOCOL_FAILURE, e.what()}, this};
            }
        }
        case (SignUp): {
            const auto signUpRequest = dynamic_cast<SignUpRequest*>(request);
            if (!signUpRequest) return {{PROTOCOL_FAILURE, "Request type is invalid!"}, this};

            try {
                signUp(signUpRequest->_username, signUpRequest->_password, signUpRequest->_email);
            }
            catch (std::runtime_error& e) {
                return {{PROTOCOL_FAILURE, e.what()}, this};
            }

            return {{PROTOCOL_SUCCESS}, this}; // TODO: change to a new request handler that will replace the login one.
        }
        default:
            return {{PROTOCOL_FAILURE, "Attribute 'code' is invalid!"}, this};
    }
}

/*
 * Logs in an existing user.
 * INPUT: username: string. password: string.
 * OUTPUT: true for success. false for failure. std::runtime_error for errors.
 */
bool LoginRequestHandler::login(const std::string& username, const std::string &password) {
    if (_db->verifyUser(username, password)) {
        _loggedUsers.push_back(LoggedUser{username});
        return true;
    }
    return false;
}

/*
 * Signs up a new user and logs them in automatically.
 * INPUT: username: string. password: string. email: string.
 * OUTPUT: true for success. std::runtime_error for errors.
 */
bool LoginRequestHandler::signUp(const std::string& username, const std::string& password, const std::string& email) {
    _db->addUser(username, password, email);
    _loggedUsers.push_back(LoggedUser{username});
    return true;
}
