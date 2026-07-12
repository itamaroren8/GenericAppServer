//
// Created by itamar on 7/12/26.
//

#ifndef APP_IREQUESTHANDLER_H
#define APP_IREQUESTHANDLER_H
#include <vector>

#include "Requests.h"


class IRequestHandler {
public:
    virtual bool handleRequest(IRequest*) = 0;
};


#endif //APP_IREQUESTHANDLER_H
