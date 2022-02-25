#include "services/authenticationservice.h"
#include "services/dataservice.h"
#include "models/user.h"

dataservice _data;

authenticationservice::authenticationservice(){

}


int authenticationservice::login(QString eml, QString pssword, int rememberMe){
    /**
    * This method handles all the logic to authenticate a user and takes in the users email, password and if they want to stay logged in. \n
    * If the user has successfully logged in then the method will return 1 to indicate success, if the user failed to log in then the method would return 0.
    */
    if(QSqlDatabase::database().isOpen()){
        QSqlQuery q;
        QString query = "SELECT * FROM users WHERE email='"+eml+"' AND password='"+pssword+"'";
        if(q.exec(query)){
            int count =0;
            int id;
            QString fname;
            QString sname;
            QString usrRle;
            QString pin;
            while(q.next()){
                count++;
                id = q.value(0).toInt();
                fname = q.value(1).toString();
                sname = q.value(2).toString();
                usrRle = q.value(5).toString();
                pin = q.value(6).toString();
            }

            if(count==1){
                std::cout << "Foud user!";
                user usr(id, fname, sname, eml, rememberMe, usrRle, pin);
                usr.setCurrentUser(usr);
                return 1;
            }
            else if(count>1){
                std::cout << "Duplicate username and password" << std::endl;
                return 0;
            }
            else if(count<1){
                std::cout << "Username and password is not correct" << std::endl;
                return 0;
            }
        }
        else {
            qDebug() << q.lastError().text();
            std::cout << "Error with query";
            return 0;
        }
    }
    else{

        _data.connectToDb();
        return 0;
    }
}

int authenticationservice::registerUsr(QString firstname, QString surname, QString email, QString password, QString password2, QString role, QString pin){
    /**
    * This method handles the logic to register a new user and takes in all the fields on the registration form as arguments.\n
    * If the user has successfully registered then the method will return 1, otherwise the method will return 0.
    */
    if(QSqlDatabase::database().isOpen()){
        QMessageBox messageBox;
        Validator _validator;
        if(_validator.registrationValidation(firstname, surname, email, password, password2) == 1){
            QSqlQuery q;
            q.prepare("INSERT INTO users (firstname, surname, email, password, role, pin) "
                      "VALUES (:fname, :sname, :eml, :pssword, :role, :pin)");
            q.bindValue(":fname", firstname);
            q.bindValue(":sname", surname);
            q.bindValue(":eml", email);
            q.bindValue(":pssword", password);
            q.bindValue(":role", role);
            q.bindValue(":pin", pin);
            if(q.exec()){
                std::cout << "Added user" << std::endl;
                return 1;
            }
            else{
                qDebug() << q.lastError().text();
                std::cout << "Failed to add user" << std::endl;
                return 0;
            }
        }
        else
            return 0;
    }
    else{
        _data.connectToDb();
        return 0;
    }
}

bool authenticationservice::quickLogin(QString pin){
    /**
    * This method handles the logic to authenticate a user using thier pin and will return true if authentication was successful. To preform the authentication a pin is required
    * as an argument.
    */
    if(pin == usr.getPin()){
        return true;
    }
    else
        return false;
}
