//
// Created by itamar on 7/13/26.
//

#ifndef APP_JSONDESERIALIZER_H
#define APP_JSONDESERIALIZER_H
#include <vector>

#include "Requests.h"


class JsonDeserializer {
public:
    static IRequest* deserializeLoginRequest(const std::string& buffer);
};


#endif //APP_JSONDESERIALIZER_H
