#include "registerform.h"
#include "ui_registerform.h"
#include "mainwindow.h"

RegisterForm::RegisterForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
    connect(ui->AlreadyHaveAcc, SIGNAL(released()), this, SLOT(onAlreadyGotAccountPressed()));
    connect(ui->RegisterBtn, SIGNAL(released()), this, SLOT(onRegisterPressed()));
}

void RegisterForm::onAlreadyGotAccountPressed(){
    this->hide();
    LoginForm login;
    login.setModal(true);
    login.exec();
}

void RegisterForm::onRegisterPressed(){
    QMessageBox messageBox;
    authenticationservice _auth;
    if(_auth.registerUsr(ui->Firstname->text(), ui->Surname->text(), ui->Email->text(), ui->Password->text(), ui->ConfirmPass->text()) == 1){
        messageBox.addButton("Login",QMessageBox::YesRole);
        messageBox.setText("Thankyou for signing up");
        messageBox.setWindowTitle("Success!");
        messageBox.exec();
        this->hide();
        LoginForm login;
        login.setModal(true);
        login.exec();
    }
    else{

    }
}

RegisterForm::~RegisterForm()
{
    delete ui;
}
