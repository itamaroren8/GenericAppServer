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
    while (1) {
        std::cout << "Choose an option:\n1. Add user\n2. Add user with score\n3. Remove user\n4. Add score to user\n5. List users\n";
        int option;
        std::cin >> option;
        std::string username;
        int score;
        switch (option) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                _db->addUser(username);
                break;
            case 2:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter score: ";
                std::cin >> score;
                _db->addUser(username, score);
                break;
            case 3:
                std::cout << "Enter username: ";
                std::cin >> username;
                _db->removeUser(username);
                break;
            case 4:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter score: ";
                std::cin >> score;
                _db->addUserScore(username, score);
                break;
            case 5:
                for (const std::string& user : _db->getUsers()) {
                    std::cout << user << "\n";
                }
                break;
            default:
                std::cout << "Invalid choice!";
                break;
        }

        std::cout << "\n";
    }
}
