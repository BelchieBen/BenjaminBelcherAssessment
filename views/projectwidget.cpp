#include "projectwidget.h"
#include "ui_projectwidget.h"

ProjectWidget::ProjectWidget(QWidget *parent,int projectId, QString ttle, QString desc, QString stus, QString mnger) :
    QWidget(parent),
    ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    this->title = ttle;
    this->description = desc;
    this->status = stus;
    this->manager = mnger;
    this->id = projectId;

    ui->ProjectTitle->setText(title);
    ui->Description->setText(description);
    ui->Manager->setText(manager);
    ui->Status->setText(status);

    connect(ui->OpenProjectBtn, SIGNAL(released()), this, SLOT(onOpenClicked()));

    changeStatusColor();
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::changeStatusColor()
{
    if(status == states.getState("NotStarted")){
        ui->frame_2->setStyleSheet("background-color: rgb(47, 64, 81)");
        ui->Status->setStyleSheet("color:rgb(255, 255, 255)");
    }

    if(status == states.getState("InProgress")){
        ui->frame_2->setStyleSheet("background-color: rgb(38, 71, 218)");
        ui->Status->setStyleSheet("color:rgb(255, 255, 255)");
    }

    if(status == states.getState("Completed")){
        ui->frame_2->setStyleSheet("background-color:rgb(30, 223, 146)");
    }
}

void ProjectWidget::onOpenClicked()
{
    emit openProject(id);
}
