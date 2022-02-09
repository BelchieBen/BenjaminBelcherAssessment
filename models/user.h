#ifndef USER_H
#define USER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>


class user
{
private:
    int id;
    QString firstname;
    QString surname;
    QString email;
    QString password;
    int currentUser;
    int rememberMe;
    QString role;
    QString pin;

public:
    user();
    user(
        int uid,
        QString frstname,
        QString srname,
        QString eml,
        int remMe,
        QString rle,
        QString loginPin
        ){
        this->id = uid;
        this->firstname = frstname;
        this->surname = srname;
        this->email = eml;
        this->rememberMe = remMe;
        this->role = rle;
        this->pin = loginPin;
    }

    user getCurrentUser(int uid);
    void setCurrentUser(user u);
    void removeCurrentUsr();
    bool isRememberMeTrue();
    void quickLogin();
    QString GetCurrentUserEmail();
    QString getUserRole();
    user getCurrentUser();
    QString getPin();
    int getUserId(QString email);
};

#endif // USER_H
