#include "authenticationservice.h"
#include "dataservice.h"

dataservice _data;


int authenticationservice::login(QString eml, QString pssword){
    if(QSqlDatabase::database().isOpen()){
        QSqlQuery q;
        QString query = "SELECT * FROM users WHERE email='"+eml+"' AND password='"+pssword+"'";
        if(q.exec(query)){
            int count =0;
            while(q.next()){
                count++;
            }

            if(count==1){
                cout << "Foud user!";
                return 1;
            }
            else if(count>1){
                cout << "Duplicate username and password" << endl;
                return 0;
            }
            else if(count<1){
                cout << "Username and password is not correct" << endl;
                return 0;
            }
        }
        else {
            qDebug() << q.lastError().text();
            cout << "Error with query";
            return 0;
        }
    }
    else{

        _data.connectToDb();
        return 0;
    }
}

int authenticationservice::registerUsr(QString firstname, QString surname, QString email, QString password, QString password2){
    if(QSqlDatabase::database().isOpen()){
        QSqlQuery q;
        QString query = "INSERT INTO users (firstname, surname, email, password) VALUES ('"+firstname+"','"+surname+"','"+email+"','"+password+"')";
//        q.prepare("INSERT INTO users (firstname, surname, email, password) "
//                  "VALUES (:fname, :sname, :eml, :pssword)");
//        q.bindValue(":fname", firstname);
//        q.bindValue(":sname", surname);
//        q.bindValue(":eml", email);
//        q.bindValue(":pssword", password);
        if(q.exec(query)){
            cout << "Added user" << endl;
            return 1;
        }
        else{
            qDebug() << q.lastError().text();
            cout << "Failed to add user" << endl;
            return 0;
        }
    }
    else{
        _data.connectToDb();
        return 0;
    }
}
