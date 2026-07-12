//
// Created by itamar on 7/5/26.
//

#include "Server.h"

#include <iostream>

#include "SqliteDatabase.h"

Server::Server() {
    _db = new SqliteDatabase(); // Change to whichever database type wanted
}

void Server::run() {
    _db->open();

    try {
        _db->addUser("Itamar", "1234", "email@email.com");
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Itamar", "1234") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        _db->removeUser("Itamar", "1234");
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Itamar", "1234") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Example", "Example") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        _db->addUser("Itamar", "1234", "email@email.com");
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Itamar", "1234") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        _db->changeUserPassword("Itamar", "1234", "12345");
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Itamar", "1234") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << _db->verifyUser("Itamar", "12345") << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        _db->changeUserPassword("Itamar", "12345", "1234");
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

    try {
        for (auto user : _db->getUsers()) {
            std::cout << user << "\n";
        }
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }

}
