#include "views/forms/loginform.h"
#include "ui_loginform.h"
#include "models/user.h"
#include "views/maindashboard.h"

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    connect(ui->LoginBtn, SIGNAL(released()), this, SLOT(onLoginPressed()));
    connect(ui->NewHereBtn, SIGNAL(released()), this, SLOT(onNewHerePressed()));
}

void LoginForm::onLoginPressed(){
    QMessageBox popup;
    user usr;
    int remMe = ui->RememberMe->isChecked();
    QString email = ui->Email->text();
    QString password = ui->Password->text();

    if(_auth.login(email, password, remMe) == 1){
        popup.setText("Login success");
        popup.exec();
        this->hide();
        LoginLandingPage landingPg;
        landingPg.setModal(true);
        landingPg.exec();
//        MainDashboard dashboard;
//        dashboard.setModal(true);
//        dashboard.showFullScreen();
//        dashboard.setWindowFlags(Qt::Window);
//        dashboard.exec();

    }
    else{
        popup.critical(0,"Login Failed","Your Email or Password is incorrect!");
        popup.setFixedSize(500,200);
    }

}

void LoginForm::onNewHerePressed(){
    this->hide();
    RegisterForm regForm;
    regForm.setModal(true);
    regForm.exec();
}

LoginForm::~LoginForm()
{
    delete ui;
}
