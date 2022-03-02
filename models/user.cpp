#include "user.h"

user::user()
{

}

user user::getCurrentUser(int u){
    /**
    * This method takes in the user ID as a paramater and then queries the user table in the database to find the matching user. It also returns a user object so all the
    * properties of the user can be used.
    */
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
    /**
    * This method is an overloaded method of getCurrentUser but doesnt require a paramater, instead it queries the current user table in the dataabse to get the current user.
    * this method is used when the user ID is not known.
    */
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
    /**
    * This method returns the current users email, however it does this by querying the current user table in the database and simply returns a QString of the email
    */
    QSqlQuery q;
    q.prepare("SELECT * FROM currentUsr");
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
    /**
    * This method takes a user object as a paramater and will first remove the current user stored in the database if there is one and then insert this user so it can be referenced
    * elsewhere in the applicaion.
    */
    removeCurrentUsr();
    QSqlQuery q;
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

int user::getUserId(QString email){
    /**
    * This method takes in a users email as a paramater and then query the users table in the database for that user and then return the users id.
    */
    int uId;
    QSqlQuery q;
    q.prepare("SELECT * from users WHERE email = :eml");
    q.bindValue(":eml", email);
    if(q.exec()){
        while(q.next()){
            uId = q.value(0).toInt();
        }
    }
    return uId;
}

void user::removeCurrentUsr(){
    /**
    * This method removes the current user from the database by preforming a DELETE query.
    */
    QSqlQuery q;
    QString query = "DELETE FROM currentUsr WHERE id=1";
    if(q.exec(query)){
        std::cout << "Removed current user" << std::endl;
    }
    else{
        std::cout << "Couldnt remove current user" << std::endl;
        qDebug() << q.lastError().text();
    }
}

bool user::isRememberMeTrue(){
    /**
    * This method queries the current user table and evaluates if the current user has selected remeber me. If remember me is true then the method will return true.
    */
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
    /**
    * This method queries the current user table in the database and will return that users role in the type of a QString
    */
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
    /**
    * This method queries the current user table in the database and will return that users quick login pin in the type of a QString
    */
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

QString user::returnEmail(int uId){
    /**
    * This method takes in the user ID as a paramater and then queries the user table in the database to find the matching user. It returns matching users email.
    */
    QSqlQuery q;
    QString email;
    QString qry = "SELECT * FROM users where id ='"+QString::number(uId)+"'";
    //q.prepare("SELECT * FROM users where id = :ii");
    //q.bindValue(":eml", QString::number(uId));
    if(q.exec(qry)){
        while(q.next()){
            email = q.value(3).toString();
        }
    }
    return email;
}

QString user::returnFirstname(){
    /**
    * This method returns the current user object's firstname
    */
    return this->firstname;
}
QString user::returnSurname(){
    /**
    * This method returns the current user object's surname
    */
    return this->surname;
}
QString user::returnEmail(){
    /**
    * This method returns the current user object's email
    */
    return this->email;
}
QString user::returnRole(){
    /**
    * This method returns the current user object's role
    */
    return this->role;
}

void user::quickLogin(){

}
