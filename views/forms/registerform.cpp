#include "views/forms/registerform.h"
#include "ui_registerform.h"
#include "mainwindow.h"

RegisterForm::RegisterForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
    ui->PinEntry->setValidator(new QIntValidator(0, 100, this));
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
    if(_auth.registerUsr(ui->Firstname->text(), ui->Surname->text(), ui->Email->text(), ui->Password->text(), ui->ConfirmPass->text(), roles.getRole("employee"), ui->PinEntry->text()) == 1){
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
