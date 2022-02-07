#include "newprojectform.h"
#include "ui_newprojectform.h"
#include "projectdataservice.h"

NewProjectForm::NewProjectForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectForm)
{
    ui->setupUi(this);
    connect(ui->CreateProjectBtn, SIGNAL(released()), this, SLOT(onCreateProjectBtnClicked()));

    createListMenus();

    // Populating the available users list with users from database
    QSqlQuery q;
    q.prepare("SELECT * from users");
    if(q.exec()){
        QString email;
        while(q.next()){
            email = q.value(1).toString();
            ui->AvailableUsersList->addItem(email);
        }
    }
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

void NewProjectForm::createListMenus(){
    auto AssignUser = new QAction("Assign to project", this);
    connect(AssignUser, SIGNAL(triggered()), this, SLOT(assignUser()));
    ui->AvailableUsersList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->AvailableUsersList->addActions({AssignUser});

    auto RemoveUser = new QAction("Remove from project", this);
    connect(RemoveUser, SIGNAL(triggered()), this, SLOT(removeUser()));
    ui->AssignedUsersList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->AssignedUsersList->addActions({RemoveUser});
}

void NewProjectForm::assignUser(){
    QListWidget *list = ui->AvailableUsersList;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *user = list->takeItem(list->currentRow());
        ui->AssignedUsersList->addItem(user);
    }
}

void NewProjectForm::removeUser(){
    QListWidget *list = ui->AssignedUsersList;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *user = list->takeItem(list->currentRow());
        ui->AvailableUsersList->addItem(user);
    }
}

NewProjectForm::~NewProjectForm()
{
    delete ui;
}
