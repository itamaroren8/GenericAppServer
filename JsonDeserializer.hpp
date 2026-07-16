//
// Created by itamar on 7/13/26.
//

#ifndef APP_JSONDESERIALIZER_H
#define APP_JSONDESERIALIZER_H
#include <memory>
#include <vector>

#include "Requests.hpp"


class JsonDeserializer {
public:
    static std::unique_ptr<IRequest> deserializeLoginRequest(const std::string& buffer);
};


#endif //APP_JSONDESERIALIZER_H
