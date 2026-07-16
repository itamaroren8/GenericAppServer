//
// Created by itamar on 7/5/26.
//

#include "SqliteDatabase.hpp"

#include <iostream>

#include "SqliteStatements.hpp"

SqliteDatabase::~SqliteDatabase() {
    SqliteDatabase::close();
}

/*
 * Opens a new sqlite database.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::open() {
    if (sqlite3_open_v2(DATEBASE_FILE, &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, nullptr))
        throw std::runtime_error("Couldn't open database!");

    if (sqlite3_exec(_db, CREATE_USERS_TABLE, nullptr, nullptr, &_errMsg) != SQLITE_OK) {
        throw std::runtime_error(_errMsg);
    }

    if (sqlite3_exec(_db, CREATE_TIMERS_TABLE, nullptr, nullptr, &_errMsg) != SQLITE_OK) {
        throw std::runtime_error(_errMsg);
    }

    return 0;
}

/*
 * Closes the database. Database is unusable after calling the function.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::close() {
    sqlite3_free(_errMsg);
    if (sqlite3_close(_db) != SQLITE_OK)
        return 1;

    return 0;
}

/*
 * Inserts a new user to the database.
 * INPUT: username: string. password: string. email: string.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::addUser(const std::string username, const std::string password) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, ADD_NEW_USER, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Adding user failed!");
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Removes an existing user from the database.
 * INPUT: username: string. password: string.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::removeUser(const std::string username, const std::string password) {
    if (!verifyUser(username, password)) throw std::runtime_error("Couldn't verify user. Please check username and password!");

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, DELETE_EXISTING_USER, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Removing user failed!");
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Adds score to an existing player.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::changeUserPassword(const std::string username, const std::string currentPassword, const std::string newPassword) {
    if (!verifyUser(username, currentPassword)) throw std::runtime_error("Couldn't verify user. Please check username and password!");

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, UPDATE_PLAYER_PASSWORD, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Changing password failed!");
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Returns a vector containing all users in database.
 * OUTPUT: A list of all users: std::vector<std::string>.
 */
std::vector<std::string> SqliteDatabase::getUsers() {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, GET_ALL_USERS, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    std::vector<std::string> users;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        users.push_back(user);
    }

    sqlite3_finalize(stmt);
    return users;
}

/*
 * Checks if user exists with username and password.
 * INPUT: username: string. password: string.
 * OUTPUT: true if user exists, false otherwise. std::runtime_error if failed to verify.
 */
bool SqliteDatabase::verifyUser(const std::string username, const std::string password) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, VERIFY_USER, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const int result = sqlite3_column_int(stmt, 0) == 1;
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    throw std::runtime_error("Verifying user failed!");
}

int SqliteDatabase::addTimer(std::string timerName, std::string timerCreator, int timerStart, int timerDuration) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, ADD_NEW_TIMER, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_text(stmt, 1, timerName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, timerCreator.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, timerStart);
    sqlite3_bind_int(stmt, 4, timerDuration);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Adding timer failed!");
    }

    sqlite3_finalize(stmt);
    return 0;
}

int SqliteDatabase::deleteTimer(int timerId) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, DELETE_EXISTING_TIMER, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    sqlite3_bind_int(stmt, 1, timerId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Removing timer failed!");
    }

    sqlite3_finalize(stmt);
    return 0;
}

std::vector<Timer> SqliteDatabase::getTimers() {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, GET_ALL_TIMERS, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement!");

    std::vector<Timer> timers;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const int timerId = sqlite3_column_int(stmt, 0);
        const std::string timerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const std::string timerCreator = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const int timerStart = sqlite3_column_int(stmt, 3);
        const int timerDuration = sqlite3_column_int(stmt, 4);

        Timer timer(timerId, timerName, timerCreator, timerStart, timerDuration);
        timers.push_back(timer);
    }

    sqlite3_finalize(stmt);
    return timers;
}
