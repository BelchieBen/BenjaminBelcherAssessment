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

public:
    user();
    user(
        int uid,
        QString frstname,
        QString srname,
        QString eml
        ){
        this->id = uid;
        this->firstname = frstname;
        this->surname = srname;
        this->email = eml;
    }

    user getCurrentUser(int uid);
    void setCurrentUser(user u);
    void removeCurrentUsr();
};

#endif // USER_H
