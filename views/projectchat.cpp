#include "projectchat.h"
#include "ui_projectchat.h"

ProjectChat::ProjectChat(QWidget *parent, int projId) :
    QWidget(parent),
    ui(new Ui::ProjectChat)
{
    ui->setupUi(this);
    this->projectId = projId;
    QString projectTitle = _projDataService.getProjectTitle(projectId);
    ui->BackToProjectBtn->setText("Back to "+projectTitle);
    ui->TitleLbl->setText(projectTitle);
    connect(ui->BackToProjectBtn, SIGNAL(released()), this, SLOT(returnToProject()));
}

void ProjectChat::returnToProject(){
    emit returnToProjectDashboard();
}

ProjectChat::~ProjectChat()
{
    delete ui;
}
