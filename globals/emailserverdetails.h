#ifndef EMAILSERVERDETAILS_H
#define EMAILSERVERDETAILS_H

#include "QString"

class EmailServerDetails
{
public:
    EmailServerDetails();
    QString getUsername();
    QString getPassword();
    QString getServerAddress();
    int getPort();
};

#endif // EMAILSERVERDETAILS_H
