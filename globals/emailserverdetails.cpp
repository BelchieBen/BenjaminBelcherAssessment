#include "emailserverdetails.h"

EmailServerDetails::EmailServerDetails()
{

}

QString EmailServerDetails::getUsername(){
    /**
    * This method returns the email address of the applications email client
    */
    return "systemwms3@gmail.com";
}

QString EmailServerDetails::getPassword(){
    /**
    * This method returns the password of the applications email client
    */
    return "Testing321?";
}

QString EmailServerDetails::getServerAddress(){
    /**
    * This method returns the email server address of the application email client
    */
    return "smtp.gmail.com";
}

int EmailServerDetails::getPort(){
    /**
    * This method returns the port to be used on the applications email client
    */
    return 465;
}
