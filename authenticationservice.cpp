#include "authenticationservice.h"
#include "dataservice.h"

dataservice _data;


int authenticationservice::login(QString eml, QString pssword){
    if(QSqlDatabase::database().isOpen()){
        QSqlQuery q;
        QString query = "SELECT * FROM users WHERE email = "+eml+" AND password = "+pssword;
        if(q.exec(query)){
            return 1;
            cout << "Foud user!";
        }
        else {
            cout << "Error with query";
            return 0;
        }
    }
    else{

        _data.connectToDb();
        return 0;
    }
}
