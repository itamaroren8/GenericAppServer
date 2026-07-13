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
    LoginRequestHandler(IDatabase* db);
    bool handleRequest(IRequest* request) override;
private:
    LoggedUser login(std::string username, std::string password);
    bool signUp(std::string username, std::string password, std::string email);
    IDatabase* _db;
};

enum LoginRequestCodes {
    Login,
    SignUp
};

#endif //APP_LOGINREQUESTHANDLER_H
