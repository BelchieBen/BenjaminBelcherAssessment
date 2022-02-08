#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include "utils/validator.h"
#include "models/user.h"

using namespace std;

class authenticationservice{
private:
    string email;
    string password;
    user usr;

public:
    authenticationservice();
    int login(QString email, QString password, int rememberMe);
    int registerUsr(QString firstname, QString surname, QString email, QString password, QString password2, QString role, QString pin);
    bool quickLogin(QString pin);


};

#endif
