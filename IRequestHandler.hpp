//
// Created by itamar on 7/12/26.
//

#ifndef APP_IREQUESTHANDLER_H
#define APP_IREQUESTHANDLER_H
#include <vector>

#include "Requests.hpp"
#include "results.hpp"


class IRequestHandler {
public:
    virtual IResult handleRequest(std::unique_ptr<IRequest>) = 0;
    virtual ~IRequestHandler() = default;
    virtual std::string serializeResponse(const IResponse&) = 0;
    virtual std::unique_ptr<IRequest> deserializeRequest(const std::string&) = 0;
};


#endif //APP_IREQUESTHANDLER_H
