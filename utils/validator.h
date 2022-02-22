#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QMessageBox>
#include <QRegularExpression>

/**
* This is a utility class that validates user inputs for the authentication service.
*/

class Validator
{
public:
    Validator();

    int registrationValidation(QString firstname, QString surname, QString email, QString password, QString password2);
    bool validateEmail(QString email);;
    bool confirmPasswords(QString password, QString password2);
};

#endif // VALIDATOR_H
