//
// Created by itamar on 7/5/26.
//

#include "SqliteDatabase.h"

#include <iostream>

#include "SqliteStatements.h"

SqliteDatabase::~SqliteDatabase() {
    SqliteDatabase::close();
}

/*
 * Opens a new sqlite database.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::open() {
    if (sqlite3_open(DATEBASE_FILE, &_db))
        return 1;

    if (sqlite3_exec(_db, CREATE_USERS_TABLE, nullptr, nullptr, &_errMsg) != SQLITE_OK) {
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
 * INPUT: username: string.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::addUser(const std::string username) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, ADD_NEW_USER, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, 0);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(_db));
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Inserts a new user to the database.
 * INPUT: username: string. score: int.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::addUser(const std::string username, const int score) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, ADD_NEW_USER, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, score);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(_db));
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Removes an existing user from the database.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::removeUser(const std::string username) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, DELETE_EXISTING_USER, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(_db));
    }

    sqlite3_finalize(stmt);
    return 0;
}

/*
 * Adds score to an existing player.
 * OUTPUT: 0 for success. std::runtime_error for failure.
 */
int SqliteDatabase::addUserScore(const std::string username, const int score) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, UPDATE_PLAYER_SCORE, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, score);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(_db));
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
    sqlite3_prepare_v2(_db, GET_ALL_USERS, -1, &stmt, nullptr);

    std::vector<std::string> users;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        users.push_back(user);
    }

    sqlite3_finalize(stmt);
    return users;
}
