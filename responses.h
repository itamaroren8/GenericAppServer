//
// Created by itamar on 7/13/26.
//

#ifndef APP_RESPONSES_H
#define APP_RESPONSES_H
#include <string>

class IResponse {
public:
    IResponse(const int code) : _code(code) {}
    IResponse(const int code, const std::string& message) : _code(code), _message(message) {}
    ~IResponse() = default;
    int _code;
    std::string _message;
};

#endif //APP_RESPONSES_H
