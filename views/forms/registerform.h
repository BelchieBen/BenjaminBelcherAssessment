#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>
#include "globals/userroles.h"
#include <QIntValidator>
#include "services/authenticationservice.h"

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

private:
    Ui::RegisterForm *ui;
    UserRoles roles;
    authenticationservice _auth;

private slots:
    void onAlreadyGotAccountPressed();
    void onRegisterPressed();
};

#endif // REGISTERFORM_H
