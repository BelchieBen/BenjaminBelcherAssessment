#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataservice.h"
#include "authenticationservice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dataservice _data;

    if(_data.connectToDb() == 1)
        cout << "Connected to database";

    connect(ui->LoginBtn, SIGNAL(released()), this, SLOT(onLoginPressed()));
}

void MainWindow::onLoginPressed(){
    QMessageBox popup;
    authenticationservice _auth;
    QString email = ui->Email->text();
    QString password = ui->Password->text();
    if(_auth.login(email, password) == 1){
        popup.setText("Login success");
        popup.exec();
    }
    else{
        popup.setText("Login Failed");
        popup.exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

