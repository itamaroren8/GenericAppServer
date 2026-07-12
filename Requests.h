//
// Created by itamar on 7/12/26.
//

#ifndef APP_REQUESTS_H
#define APP_REQUESTS_H
#include <string>

class IRequest {
public:
    virtual ~IRequest() = default;
    int code;
};

class LoginRequest : public IRequest {
public:
    std::string username;
    std::string password;
};

class SignUpRequest : public IRequest {
public:
    std::string username;
    std::string password;
    std::string email;
};

#endif //APP_REQUESTS_H
