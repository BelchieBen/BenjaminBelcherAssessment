#ifndef USER_H
#define USER_H
#include <QString>
#include <QSqlQuery>
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

public:
    user();
    user(
        int uid,
        QString frstname,
        QString srname,
        QString eml,
        int remMe
        ){
        this->id = uid;
        this->firstname = frstname;
        this->surname = srname;
        this->email = eml;
        this->rememberMe = remMe;
    }

    user getCurrentUser(int uid);
    void setCurrentUser(user u);
    void removeCurrentUsr();
    bool isRememberMeTrue();
    void quickLogin();
};

#endif // USER_H
