#include "newprojectform.h"
#include "ui_newprojectform.h"
#include "projectdataservice.h"

NewProjectForm::NewProjectForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectForm)
{
    ui->setupUi(this);
    connect(ui->CreateProjectBtn, SIGNAL(released()), this, SLOT(onCreateProjectBtnClicked()));
}

void NewProjectForm::onCreateProjectBtnClicked(){
    ProjectDataService _dataService;
    QMessageBox _messageBox;
    QString title = ui->ProjTitle->text();
    QString desc = ui->ProjDesc->toPlainText();
    QString status = ui->StatusBox->currentText();
    QString manager = ui->ProjectManagerBox->currentText();
    QVector<QString> usrs;
    QListWidget *usrslist = ui->AssignedUsersList;
    int count = 0;
    for(auto item: usrslist->findItems("*",Qt::MatchWildcard)){
        QString i = item->data(0).toString();
        usrs.append(i);
    }
    if(_dataService.createProject(title, desc, status, manager)){
        int projectId = _dataService.getProject(title);
        if(_dataService.insertProjUsers(usrs, projectId)){
            _messageBox.setText("Created Project "+title);
            _messageBox.exec();
            this->hide();
            ui->ProjTitle->setText("");
            ui->ProjDesc->setPlainText("");
            ui->StatusBox->setCurrentIndex(0);
            ui->ProjectManagerBox->setCurrentIndex(0);
            ui->AssignedUsersList->clear();
        }
    }
    else{
        _messageBox.critical(0,"Error","There was an error when creating the project, please try again!");
    }
}

NewProjectForm::~NewProjectForm()
{
    delete ui;
}
