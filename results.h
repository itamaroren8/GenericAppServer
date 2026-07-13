//
// Created by itamar on 7/13/26.
//

#ifndef APP_RESULTS_H
#define APP_RESULTS_H
#include "IRequestHandler.h"
#include "responses.h"

class IRequestHandler;

class IResult {
public:
    IResult(const IResponse response, IRequestHandler* requestHandler) : _response(response), _requestHandler(requestHandler) {}
    IResponse _response;
    IRequestHandler* _requestHandler;
};

#endif //APP_RESULTS_H
