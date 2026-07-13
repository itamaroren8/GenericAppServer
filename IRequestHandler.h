//
// Created by itamar on 7/12/26.
//

#ifndef APP_IREQUESTHANDLER_H
#define APP_IREQUESTHANDLER_H
#include <vector>

#include "Requests.h"
#include "results.h"


class IRequestHandler {
public:
    virtual IResult handleRequest(IRequest*) = 0;
    virtual ~IRequestHandler() = default;
    virtual std::vector<char> serializeResponse(const IResponse&) = 0;
    virtual IRequest* deserializeRequest(const std::vector<char>&) = 0;
};


#endif //APP_IREQUESTHANDLER_H
