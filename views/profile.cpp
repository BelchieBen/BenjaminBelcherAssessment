#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    user u = usr.getCurrentUser();
    ui->WelcomeLbl->setText("Hello "+u.returnFirstname());
    ui->Firstname->setText(u.returnFirstname());
    ui->Surname->setText(u.returnSurname());
    ui->Email->setText(u.returnEmail());
    ui->Role->setText(u.returnRole());
    populateTreeWidget();

    connect(ui->MainDashboardBtn, SIGNAL(released()), this, SLOT(returnToMainDashboard()));

}

void Profile::returnToMainDashboard(){
    emit returnToDashboard();
}

void Profile::populateTreeWidget(){
    QTreeWidget *tree = ui->treeWidget;
    delete tree->takeTopLevelItem(0);
    QTreeWidgetItem *topLevel = new QTreeWidgetItem();
    topLevel->setText(0, "This the projects col");
    for (int i=0; i<5 ;i++ ) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, "Task "+ QString::number(i+1));
        topLevel->addChild(item);
    }

    tree->setHeaderItem(topLevel);

    for(int i=0; i<5; i++)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem();
        item->setText(0,"top-level " + QString::number(i+1));
        tree->addTopLevelItem(item);
    }
}

Profile::~Profile()
{
    delete ui;
}
