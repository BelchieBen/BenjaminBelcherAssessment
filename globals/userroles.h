#ifndef USERROLES_H
#define USERROLES_H

#include <QString>
#include <QMap>


class UserRoles
{
public:
    UserRoles();
    QMap<QString, QString> roles;
    QString getRole(QString role);
};

#endif // USERROLES_H
