#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <iostream>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDir>

using namespace std;

class dataservice
{
public:
    dataservice();

    int connectToDb();
};

#endif // DATASERVICE_H
