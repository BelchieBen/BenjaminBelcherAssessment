#ifndef USER_H
#define USER_H
#include <QString>


class user
{
private:
    QString firstname;
    QString surname;
    QString email;
    QString password;

public:
    user();
    user(
        QString frstname,
        QString srname,
        QString eml,
        QString pssword
        ){
        this->firstname = frstname;
        this->surname = srname;
        this->email = eml;
        this->password = pssword;
    }
};

#endif // USER_H
