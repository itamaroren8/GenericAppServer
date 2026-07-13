//
// Created by itamar on 7/13/26.
//

#include "JsonDeserializer.h"
#include <nlohmann/json.hpp>

#include "LoginRequestHandler.h"

/*
 * Deserializes a buffer to a login request.
 * INPUT: buffer: std::vector<char>.
 * OUTPUT: IRequest*(polymorphism pointer, can point to LoginRequest or SignUpRequest).
 */
IRequest *JsonDeserializer::deserializeLoginRequest(const std::vector<char> &buffer) {
    nlohmann::json data = nlohmann::json::parse(buffer.begin(), buffer.end());

    if (!data.contains("code") || !data["code"].is_number_integer()) throw std::runtime_error("Request invalid! No 'code' attribute found, or 'code' does not match 'integer' type!");
    switch (const int code = data["code"]) {
        case Login: {
            if (!data.contains("username") || !data["username"].is_string()) throw std::runtime_error("Request invalid! No 'username' attribute found, or 'username' does not match 'string' type!");
            const std::string username = data["username"];
            if (!data.contains("password") || !data["password"].is_string()) throw std::runtime_error("Request invalid! No 'password' attribute found, or 'password' does not match 'string' type!");
            const std::string password = data["password"];

            const auto loginRequest = new LoginRequest(code, username, password);
            return loginRequest;
        }
        case SignUp: {
            if (!data.contains("username") || !data["username"].is_string()) throw std::runtime_error("Request invalid! No 'username' attribute found, or 'username' does not match 'string' type!");
            const std::string username = data["username"];
            if (!data.contains("password") || !data["password"].is_string()) throw std::runtime_error("Request invalid! No 'password' attribute found, or 'password' does not match 'string' type!");
            const std::string password = data["password"];
            if (!data.contains("email") || !data["email"].is_string()) throw std::runtime_error("Request invalid! No 'email' attribute found, or 'email' does not match 'string' type!");
            const std::string email = data["email"];

            const auto signUpRequest = new SignUpRequest(code, username, password, email);
            return signUpRequest;
        }
        default:
            throw std::runtime_error("Request invalid! Attribute 'code' does not point to a valid operation!");
    }
}
