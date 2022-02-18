#include "time.h"

Time::Time()
{

}

QString Time::getCurrentTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string localTime = asctime(localtm);
    QString qTime = QString::fromStdString(localTime);
    return qTime;
}

