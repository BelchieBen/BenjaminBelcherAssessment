#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QMessageBox>
#include "registerform.h"
#include "services/dataservice.h"
#include "services/authenticationservice.h"
#include "views/loginlandingpage.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
    authenticationservice _auth;

private slots:
    void onLoginPressed();
    void onNewHerePressed();
};

#endif // LOGINFORM_H
