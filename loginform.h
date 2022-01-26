#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QMessageBox>
#include "registerform.h"
#include "dataservice.h"
#include "authenticationservice.h"

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

private slots:
    void onLoginPressed();
    void onNewHerePressed();
};

#endif // LOGINFORM_H
