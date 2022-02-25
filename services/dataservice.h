#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <iostream>
#include <QtSql>
#include <QFileInfo>
#include <QDir>

/**
* This class is the service that handles connecting to the local database.
*/

class dataservice
{
public:
    dataservice();

    int connectToDb();
};

#endif // DATASERVICE_H
