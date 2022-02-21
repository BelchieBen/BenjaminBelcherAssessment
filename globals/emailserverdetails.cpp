#include "emailserverdetails.h"

EmailServerDetails::EmailServerDetails()
{

}

QString EmailServerDetails::getUsername(){
    return "systemwms3@gmail.com";
}

QString EmailServerDetails::getPassword(){
    return "Testing321?";
}

QString EmailServerDetails::getServerAddress(){
    return "smtp.gmail.com";
}

int EmailServerDetails::getPort(){
    return 465;
}
