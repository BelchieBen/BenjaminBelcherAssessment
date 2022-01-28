#include "maindashboard.h"
#include "ui_maindashboard.h"

MainDashboard::MainDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);
}

MainDashboard::~MainDashboard()
{
    delete ui;
}
