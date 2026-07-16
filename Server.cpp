//
// Created by itamar on 7/5/26.
//

#include "Server.hpp"

Server::Server() {
    _communicator = std::make_unique<Communicator>();
}

void Server::run() {
        _communicator->listenToClients();
}

