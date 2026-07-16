//
// Created by itamar on 7/9/26.
//

#include "Communicator.hpp"

#include <complex>

#include "CONSTANTS.hpp"
#include <iostream>
#include <thread>

#include "IRequestHandler.hpp"
#include "JsonDeserializer.hpp"
#include "JsonSerializer.hpp"
#include "LoginRequestHandler.hpp"

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
        if (const ssize_t n = socket.read(buffer, sizeof(buffer)).value(); n > 0) {
            const auto msg = std::string(buffer);
            try {
                IRequest* request = requestHandler->deserializeRequest(msg);
                IResult result = requestHandler->handleRequest(request);
                std::string serializedMsg = requestHandler->serializeResponse(result._response);

                if (requestHandler != result._requestHandler) {
                    delete requestHandler;
                    requestHandler = result._requestHandler;
                }

                socket.send(std::string(serializedMsg.begin(), serializedMsg.end()));
            }
            catch (std::runtime_error& e) {
                std::string serializedMsg = requestHandler->serializeResponse({PROTOCOL_FAILURE, e.what()});
                socket.send(std::string(serializedMsg.begin(), serializedMsg.end()));
            }

            std::cout << "Request handled successfully on thread: " << std::this_thread::get_id() << "\n";
        }
    }
}


