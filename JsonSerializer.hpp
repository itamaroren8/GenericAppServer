//
// Created by itamar on 7/13/26.
//

#ifndef APP_JSONSERIALIZER_H
#define APP_JSONSERIALIZER_H
#include <vector>

#include "responses.hpp"


class JsonSerializer {
public:
    static std::string serializeLoginResponse(const IResponse& response);
};


#endif //APP_JSONSERIALIZER_H
