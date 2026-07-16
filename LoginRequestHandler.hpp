//
// Created by itamar on 7/12/26.
//

#ifndef APP_LOGINREQUESTHANDLER_H
#define APP_LOGINREQUESTHANDLER_H
#include <memory>

#include "IDatabase.hpp"
#include "IRequestHandler.hpp"
#include "LoggedUser.hpp"
#include "Requests.hpp"


class LoginRequestHandler : public IRequestHandler {
public:
    LoginRequestHandler(IDatabase* db, std::vector<LoggedUser>& loggedUsers);
    IResult handleRequest(std::unique_ptr<IRequest> request) override;
    std::string serializeResponse(const IResponse &) override;
    std::unique_ptr<IRequest> deserializeRequest(const std::string& buffer) override;
private:
    bool login(const std::string& username, const std::string &password);
    bool signUp(const std::string& username, const std::string& password);
    IDatabase* _db;
    std::vector<LoggedUser>& _loggedUsers;
};

enum LoginRequestCodes {
    Login,
    SignUp
};

#endif //APP_LOGINREQUESTHANDLER_H
