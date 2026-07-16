//
// Created by itamar on 7/5/26.
//

#ifndef APP_SQLITEDATABASE_H
#define APP_SQLITEDATABASE_H
#include <sqlite3.h>

#include "IDatabase.hpp"

#define DATEBASE_FILE "sqliteDB.db"

class SqliteDatabase : public IDatabase{
public:
    SqliteDatabase() = default;
    ~SqliteDatabase() override;
    int open() override;
    int close() override;

    // Users
    int addUser(std::string username, std::string password) override;
    int removeUser(std::string username, std::string password) override;
    int changeUserPassword(std::string username, std::string currentPassword, std::string newPassword) override;
    bool verifyUser(std::string username, std::string password) override;
    std::vector<std::string> getUsers() override;

    // Timers
    int addTimer(std::string timerName, std::string timerCreator, int timerStart, int timerDuration) override;
    int deleteTimer(int timerId) override;
    std::vector<Timer> getTimers() override;
private:
    sqlite3* _db;
    char* _errMsg;
};


#endif //APP_SQLITEDATABASE_H
