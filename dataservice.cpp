#include "dataservice.h"

dataservice::dataservice()
{

}

int dataservice::connectToDb(){
    QString path = QDir::currentPath();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+"WMS.db");
    if(db.open())
        return 1;
    else
        return 0;
}
