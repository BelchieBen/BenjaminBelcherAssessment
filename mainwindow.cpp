#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->LoginBtn, SIGNAL(released()), this, SLOT(onLoginPressed()));
    connect(ui->RegisterBtn, SIGNAL(released()), this, SLOT(onRegisterPressed()));

}

void MainWindow::onLoginPressed(){
    this->hide();
    LoginForm login;
    login.setModal(true);
    login.exec();
}

void MainWindow::onRegisterPressed(){
    this->hide();
    RegisterForm regform;
    regform.setModal(true);
    regform.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

