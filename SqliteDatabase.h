//
// Created by itamar on 7/5/26.
//

#ifndef APP_SQLITEDATABASE_H
#define APP_SQLITEDATABASE_H
#include <sqlite3.h>

#include "IDatabase.h"

#define DATEBASE_FILE "sqliteDB.db"

class SqliteDatabase : public IDatabase{
public:
    SqliteDatabase() = default;
    ~SqliteDatabase();
    int open() override;
    int close() override;
    int addUser(std::string username, std::string password, std::string email) override;
    int removeUser(std::string username, std::string password) override;
    int changeUserPassword(std::string username, std::string currentPassword, std::string newPassword) override;
    bool verifyUser(std::string username, std::string password) override;
    std::vector<std::string> getUsers() override;
private:
    sqlite3* _db;
    char* _errMsg;
};


#endif //APP_SQLITEDATABASE_H
