//
// Created by itamar on 7/13/26.
//

#include "JsonSerializer.h"

#include <nlohmann/json.hpp>

std::vector<char> JsonSerializer::serializeLoginResponse(const IResponse& response) {
    nlohmann::json j;
    j["code"] = response._code;
    j["message"] = response._message;

    std::string jsonStr = j.dump();
    return {jsonStr.begin(), jsonStr.end()};
}
