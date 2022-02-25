#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include "utils/validator.h"
#include "models/user.h"

/**
* This class holds all the methods to authenticate a user and register a new user
*/

class authenticationservice{
private:
    std::string email;
    std::string password;
    user usr;

public:
    authenticationservice();
    int login(QString email, QString password, int rememberMe);
    int registerUsr(QString firstname, QString surname, QString email, QString password, QString password2, QString role, QString pin);
    bool quickLogin(QString pin);


};

#endif
