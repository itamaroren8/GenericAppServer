//
// Created by itamar on 7/12/26.
//

#ifndef APP_LOGINREQUESTHANDLER_H
#define APP_LOGINREQUESTHANDLER_H
#include "IDatabase.h"
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Requests.h"


class LoginRequestHandler : public IRequestHandler {
public:
    LoginRequestHandler(IDatabase* db, std::vector<LoggedUser>& loggedUsers);
    bool handleRequest(IRequest* request) override;
private:
    bool login(const std::string& username, const std::string &password);
    bool signUp(const std::string& username, const std::string& password, const std::string& email);
    IDatabase* _db;
    std::vector<LoggedUser>& _loggedUsers;
};

enum LoginRequestCodes {
    Login,
    SignUp
};

#endif //APP_LOGINREQUESTHANDLER_H
