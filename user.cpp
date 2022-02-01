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
        while(q.next()){
            count ++;
            fname = q.value(1).toString();
            sname = q.value(2).toString();
            eml = q.value(3).toString();
            remMe = q.value(4).toInt();
        }
        if(count == 1){
            user usr(u,fname,sname,eml,remMe);
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

void user::setCurrentUser(user u){
    QSqlQuery q;
    q.prepare("INSERT INTO currentUsr (id, firstname, surname, email, rememberMe) "
              "VALUES (:id, :fname, :sname, :eml, :remMe)");
    q.bindValue(":id", 1);
    q.bindValue(":fname", u.firstname);
    q.bindValue(":sname", u.surname);
    q.bindValue(":eml", u.email);
    q.bindValue(":remMe", u.rememberMe);
    try{
        q.exec();
    }
    catch (...) {

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

void user::quickLogin(){

}
