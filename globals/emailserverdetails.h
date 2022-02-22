#ifndef EMAILSERVERDETAILS_H
#define EMAILSERVERDETAILS_H

#include "QString"

/**
 * This class acts as a global information store for the authentication details regarding the Email client. This information will not change throughout the applications lifeycle
 * so by holding it staticly in one place it increases the integrity of my application.
 */

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
