//
// Created by itamar on 7/9/26.
//

#include "Communicator.h"
#include "CONSTANTS.h"
#include <iostream>
#include <thread>

Communicator::Communicator() {
    _db = new SqliteDatabase(); // Interchangeable to any implemented database class
    _db->open();
}

void Communicator::listenToClients() {
    sockpp::initialize();
    sockpp::error_code ec;
    sockpp::tcp_acceptor acc(SERVER_PORT, LISTENING_QUEUE_SIZE, ec);
    if (ec) {
        throw std::runtime_error(ec.message());
    }

    std::cout << "Server listening...\n";

    while (true) {
        auto sock = acc.accept();
        if (!sock) {
            throw std::runtime_error(sock.error_message());
        }

        std::thread workerThread([this,  socket = std::move(sock.release())]() mutable {handleClient(std::move(socket));});
        workerThread.detach();
    }
}

void Communicator::handleClient(sockpp::tcp_socket socket) {
    char buffer[BUFFER_SIZE];
    ssize_t n = socket.read(buffer, sizeof(buffer)).value();
    if (n > 0) {
        std::string msg(buffer, n);
        std::cout << msg << "\n";

        try {
            int score = _db->getUserScore(msg);
            const std::string message = "User score: " + std::to_string(score);
            socket.send(message);
        }
        catch (std::runtime_error e) {
            socket.send(e.what());
        }
    }
}


