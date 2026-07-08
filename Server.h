//
// Created by itamar on 7/5/26.
//

#ifndef APP_SERVER_H
#define APP_SERVER_H
#include "IDatabase.h"


class Server {
private:
    IDatabase* _db;
public:
    Server();
    void run();
};


#endif //APP_SERVER_H
