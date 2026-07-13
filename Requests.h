//
// Created by itamar on 7/12/26.
//

#ifndef APP_REQUESTS_H
#define APP_REQUESTS_H
#include <string>
#include <utility>

class IRequest {
public:
    IRequest(const int code) : _code(code) {}
    virtual ~IRequest() = default;
    int _code;
};

class LoginRequest : public IRequest {
public:
    LoginRequest(const int code, std::string username, std::string password) : IRequest(code), _username(std::move(username)), _password(std::move(password)) {}
    std::string _username;
    std::string _password;
};

class SignUpRequest : public IRequest {
public:
    SignUpRequest(const int code, std::string username, std::string password, std::string email) : IRequest(code), _username(std::move(username)), _password(std::move(password)), _email(std::move(email)) {}
    std::string _username;
    std::string _password;
    std::string _email;
};

#endif //APP_REQUESTS_H
