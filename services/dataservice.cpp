#include "dataservice.h"

dataservice::dataservice()
{

}

int dataservice::connectToDb(){
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
