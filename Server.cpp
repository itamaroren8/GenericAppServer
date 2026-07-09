//
// Created by itamar on 7/5/26.
//

#include "Server.h"

#include <iostream>

#include "SqliteDatabase.h"

Server::Server() {
    _communicator = new Communicator();
}

void Server::run() {
        _communicator->listenToClients();
}

