#include "user.h"

user::user()
{

}

user user::getCurrentUser(int u){
    QSqlQuery q;
    QString query = "SELECT * FROM users WHERE id='"+QString::number(u)+"'";
    if(q.exec(query)){
        int count = 0;
        QString fname;
        QString sname;
        QString eml;
        int remMe;
        QString usrRle;
        QString pin;
        while(q.next()){
            count ++;
            fname = q.value(1).toString();
            sname = q.value(2).toString();
            eml = q.value(3).toString();
            remMe = q.value(4).toInt();
            usrRle = q.value(5).toString();
            pin = q.value(6).toString();
        }
        if(count == 1){
            user usr(u,fname,sname,eml,remMe, usrRle, pin);
            return usr;
        }
        else if(count>0){
            // duplicate user for some reason
        }
        else{
            // Not found
        }
    }
}

user user::getCurrentUser(){
    QSqlQuery q;
    q.prepare("SELECT * FROM currentUsr");
    if(q.exec()){
        int count = 0;
        int id;
        QString fname;
        QString sname;
        QString eml;
        int remMe;
        QString usrRle;
        QString pin;
        while(q.next()){
            count ++;
            id = q.value(0).toInt();
            fname = q.value(1).toString();
            sname = q.value(2).toString();
            eml = q.value(3).toString();
            remMe = q.value(4).toInt();
            usrRle = q.value(5).toString();
            pin = q.value(6).toString();
        }
        if(count == 1){
            user usr(id,fname,sname,eml,remMe, usrRle, pin);
            return usr;
        }
        else if(count>0){
            // duplicate user for some reason
        }
        else{
            // Not found
        }
    }
}

QString user::GetCurrentUserEmail(){
    QSqlQuery q;
    QString query = "SELECT * FROM currentUsr";
    if(q.exec()){
        QString username;
        while(q.next()){
            username = q.value(3).toString();
        }
        return username;
    }
    return "";
}

void user::setCurrentUser(user u){
    QSqlQuery q;
    //QString qru = "INSERT INTO currentUsr (id, firstname, surname, email, rememberMe, role, pin) VALUES ('1','"+u.firstname+"','"+u.surname+"','"+u.email+"','"+QString::number(u.rememberMe)+"','"+u.role+"','"+u.pin+"')";
    q.prepare("INSERT INTO currentUsr (id, firstname, surname, email, rememberMe, role, pin) "
              "VALUES (:id, :fname, :sname, :eml, :remMe, :rle, :pin)");
    q.bindValue(":id", 1);
    q.bindValue(":fname", u.firstname);
    q.bindValue(":sname", u.surname);
    q.bindValue(":eml", u.email);
    q.bindValue(":remMe", u.rememberMe);
    q.bindValue(":rle", u.role);
    q.bindValue(":pin", u.pin);
    if(q.exec()){
        qDebug() << "Current user set";
    }
    else {
        qDebug() << q.lastError().text();
    }
}

void user::removeCurrentUsr(){
    QSqlQuery q;
    QString query = "DELETE FROM currentUsr WHERE id=1";
    if(q.exec(query)){
        std::cout << "Removed current user" << std::endl;
    }
    else{
        std::cout << "Couldnt remove current user" << std::endl;
    }
}

bool user::isRememberMeTrue(){
    QSqlQuery q;
    q.prepare("SELECT * FROM currentUsr");
    int remMe;
    if(q.exec()){
        while(q.next()){
            remMe = q.value(4).toInt();
        }
    }
    if(remMe == 1)
        return true;

    else
        return false;
}

QString user::getUserRole(){
    QSqlQuery q;
    q.prepare("SELECT * FROM currentUsr");
    QString role;
    if(q.exec()){
        while(q.next()){
            role = q.value(5).toString();
        }
    }
    return role;
}

QString user::getPin(){
    QSqlQuery q;
    q.prepare("SELECT * FROM currentUsr");
    QString pin;
    if(q.exec()){
        while(q.next()){
            pin = q.value(6).toString();
        }
    }
    return pin;
}

void user::quickLogin(){

}
