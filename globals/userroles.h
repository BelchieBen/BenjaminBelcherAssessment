#ifndef USERROLES_H
#define USERROLES_H

#include <QString>
#include <QMap>

/**
* This class holds the values of user roles which are mainly used when creating a new user or conditional statements to assert that a user has access to certian features. \n
* The values of these roles will also not change throughout the lifecycle of the applicaion so it's good practice to store the values in one location.
*/

class UserRoles
{
public:
    UserRoles();
    QMap<QString, QString> roles;
    QString getRole(QString role);
};

#endif // USERROLES_H
