//
// Created by itamar on 7/9/26.
//

#ifndef APP_COMMUNICATOR_H
#define APP_COMMUNICATOR_H
#include <sockpp/tcp_acceptor.h>

#include "LoggedUser.hpp"
#include "SqliteDatabase.hpp"


class Communicator {
private:
    SqliteDatabase* _db;
    std::vector<LoggedUser> _loggedUsers;
public:
    Communicator();
    void listenToClients();
    void handleClient(sockpp::tcp_socket socket);
};


#endif //APP_COMMUNICATOR_H
