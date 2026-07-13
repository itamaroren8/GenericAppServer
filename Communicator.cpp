//
// Created by itamar on 7/9/26.
//

#include "Communicator.h"

#include <complex.h>

#include "CONSTANTS.h"
#include <iostream>
#include <thread>

#include "IRequestHandler.h"
#include "JsonDeserializer.h"
#include "LoginRequestHandler.h"

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
    IRequestHandler* requestHandler = new LoginRequestHandler(_db, _loggedUsers);
    char buffer[BUFFER_SIZE];

    while (true) {
        const ssize_t n = socket.read(buffer, sizeof(buffer)).value();

        if (n > 0) {
            const auto msg = std::vector<char>(std::begin(buffer), std::end(buffer));
            try {
                IRequest* request = JsonDeserializer::deserializeLoginRequest(msg);
                const bool result = requestHandler->handleRequest(request);
                socket.send(std::to_string(result));
            }
            catch (std::runtime_error e) {
                socket.send(e.what());
            }
        }

        std::cout << "Request handled successfully on thread: " << std::this_thread::get_id() << "\n";
    }
}


