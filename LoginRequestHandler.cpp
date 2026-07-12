//
// Created by itamar on 7/12/26.
//

#include "LoginRequestHandler.h"

#include <stdexcept>

#include "Requests.h"

LoginRequestHandler::LoginRequestHandler(IDatabase *db) : _db(db) {}

bool LoginRequestHandler::handleRequest(IRequest* request) {
    switch (request->code) {
        case (Login): {
            const auto loginRequest = dynamic_cast<LoginRequest*>(request);
            if (!loginRequest) throw std::runtime_error("Couldn't convert request to login request!");

            return login(loginRequest->username, loginRequest->password);
        }
        case (SignUp): {
            const auto signUpRequest = dynamic_cast<SignUpRequest*>(request);
            if (!signUpRequest) throw std::runtime_error("Couldn't convert request to signup request!");

            return signUp(signUpRequest->username, signUpRequest->password, signUpRequest->email);
        }
        default:
            throw std::runtime_error("Request code is invalid!");
    }
}

bool LoginRequestHandler::login(std::string username, std::string password) {
    return true; // TODO: Add login capabilities.
}

bool LoginRequestHandler::signUp(std::string username, std::string password, std::string email) {
    return true; // TODO: Add sign up capabilities.
}
