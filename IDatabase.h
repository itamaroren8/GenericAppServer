//
// Created by itamar on 7/5/26.
//

#ifndef APP_IDATABASE_H
#define APP_IDATABASE_H
#include <string>
#include <vector>


class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual int open() = 0;
    virtual int close() = 0;
    virtual int addUser(std::string) = 0;
    virtual int addUser(std::string, int) = 0;
    virtual int removeUser(std:: string) = 0;
    virtual int addUserScore(std::string, int) = 0;
    virtual std::vector<std::string> getUsers() = 0;
};


#endif //APP_IDATABASE_H
