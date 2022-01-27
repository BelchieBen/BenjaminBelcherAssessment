#include "validator.h"

Validator::Validator()
{

}

int Validator::registrationValidation(QString firstname, QString surname, QString email, QString password, QString password2){
    QMessageBox messageBox;

    if(firstname.size() == 0){
        messageBox.critical(0,"Error","Please enter a firstname!");
        messageBox.setFixedSize(500,200);
        return 0;
    }

    else if(surname.size() == 0){
        messageBox.critical(0,"Error","Please enter a surname!");
        messageBox.setFixedSize(500,200);
        return 0;
    }

    else if(email.size() == 0){
        messageBox.critical(0,"Email Error","Please enter a email!");
        messageBox.setFixedSize(500,200);
        return 0;
    }

    else if(password.size() == 0){
        messageBox.critical(0,"Password Error","Please enter a password!");
        messageBox.setFixedSize(500,200);
        return 0;
    }
    else if(password2.size() == 0){
        messageBox.critical(0,"Password Error","Please confirm your password!");
        messageBox.setFixedSize(500,200);
        return 0;
    }

    else if(!confirmPasswords(password, password2)){
        messageBox.critical(0,"Password Error","Your passwords do not match!");
        messageBox.setFixedSize(500,200);
        return 0;
    }

    else if(!validateEmail(email)){
        messageBox.critical(0,"Email Error","Your email is not valid!");
        messageBox.setFixedSize(500,200);
        return 0;
    }
    else
        return 1;
}


bool Validator::validateEmail(QString email){
    bool isValid = true;
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!regex.match(email).hasMatch()){
        isValid = false;
    }

    return isValid;
}

bool Validator::confirmPasswords(QString password, QString password2){
    bool isValid = false;
    if(password == password2){
        isValid = true;
    }
    return isValid;
}
