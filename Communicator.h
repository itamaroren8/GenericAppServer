//
// Created by itamar on 7/9/26.
//

#ifndef APP_COMMUNICATOR_H
#define APP_COMMUNICATOR_H
#include <sockpp/tcp_acceptor.h>

#include "SqliteDatabase.h"


class Communicator {
private:
    SqliteDatabase* _db;
public:
    Communicator();
    void listenToClients();
    void handleClient(sockpp::tcp_socket socket);
};


#endif //APP_COMMUNICATOR_H
