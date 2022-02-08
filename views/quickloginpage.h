#ifndef QUICKLOGINPAGE_H
#define QUICKLOGINPAGE_H

#include <QDialog>
#include <QIntValidator>
#include "services/authenticationservice.h"
#include "views/loginlandingpage.h"
#include <QMessageBox>

namespace Ui {
class QuickLoginPage;
}

class QuickLoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit QuickLoginPage(QWidget *parent = nullptr);
    ~QuickLoginPage();

private:
    Ui::QuickLoginPage *ui;
    authenticationservice _auth;
    LoginLandingPage loginLandingPage;
    QMessageBox _messageBox;

private slots:
    void onLoginClicked();
};

#endif // QUICKLOGINPAGE_H
