#define AUTHENTICATIONSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include "validator.h"

using namespace std;

class authenticationservice{
private:
    string email;
    string password;

public:
    authenticationservice(){};
//    authenticationservice(string eml, string pssword){
//        this->email = eml;
//        this->password = pssword;
//    }

    //int hashPassword(string const &Combine);
    int login(QString email, QString password);
    int registerUsr(QString firstname, QString surname, QString email, QString password, QString password2);
    //int forgotPassword(string email);


};
