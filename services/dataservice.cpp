#include "dataservice.h"

dataservice::dataservice()
{

}

int dataservice::connectToDb(){
    /**
    * This method establishes a connection to the local SQLITE database and will return 1 if the connection is successful, otherwise it will return 0.
    */
    QString path = "C:/dev/C++/BenjaminBelcherAssessment/database/";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+"WMS.db");
    if(db.open()){
        std::cout <<"connected to db" << std::endl;
        return 1;
    }
    else
        return 0;
}
