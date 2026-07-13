//
// Created by itamar on 7/12/26.
//

#include "LoginRequestHandler.h"

#include <stdexcept>
#include <utility>

#include "LoggedUser.h"
#include "Requests.h"

LoginRequestHandler::LoginRequestHandler(IDatabase *db, std::vector<LoggedUser>& loggedUsers) : _db(db), _loggedUsers(loggedUsers) {}

/*
 * Handles a client request (Login).
 * INPUT: request: LoginRequest*.
 * OUTPUT: true for success. false for failure. std::runtime_error for errors.
 */
bool LoginRequestHandler::handleRequest(IRequest* request) {
    switch (request->_code) {
        case (Login): {
            const auto loginRequest = dynamic_cast<LoginRequest*>(request);
            if (!loginRequest) throw std::runtime_error("Couldn't convert request to login request!");

            return login(loginRequest->_username, loginRequest->_password);
        }
        case (SignUp): {
            const auto signUpRequest = dynamic_cast<SignUpRequest*>(request);
            if (!signUpRequest) throw std::runtime_error("Couldn't convert request to signup request!");

            return signUp(signUpRequest->_username, signUpRequest->_password, signUpRequest->_email);
        }
        default:
            throw std::runtime_error("Request code is invalid!");
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
