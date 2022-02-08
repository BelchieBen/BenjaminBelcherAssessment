#include "userroles.h"

UserRoles::UserRoles()
{
    roles["employee"] = "employee";
    roles["manager"] = "manager";
}

QString UserRoles::getRole(QString role){
    return roles[role];
}
