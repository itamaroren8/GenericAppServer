//
// Created by itamar on 7/5/26.
//

#include "Server.hpp"

#include <iostream>

#include "SqliteDatabase.hpp"

Server::Server() {
    _communicator = new Communicator();
}

void Server::run() {
        _communicator->listenToClients();
}

