#include "userroles.h"

UserRoles::UserRoles()
{
    /**
    * All the values of each user role get assigned in the constructor
    */
    roles["employee"] = "employee";
    roles["manager"] = "manager";
}

QString UserRoles::getRole(QString role){
    /**
    * Returns the requested role specified by the parameter
    */
    return roles[role];
}
