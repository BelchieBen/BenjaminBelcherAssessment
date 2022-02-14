#include "projectsettingspage.h"
#include "ui_projectsettingspage.h"

ProjectSettingsPage::ProjectSettingsPage(QWidget *parent, int projectId) :
    QDialog(parent),
    ui(new Ui::ProjectSettingsPage)
{
    ui->setupUi(this);
    this->projId = projectId;
    QString tle = _projDataService.getProjectTitle(projId);
    ui->Title->setText(tle+" settings");
    ui->ProjectNameEdit->setText(tle);
    connect(ui->SaveBtn, SIGNAL(released()), this, SLOT(onSaveBtnClicked()));
    populateUsersLists();
    createListMenus();
}

void ProjectSettingsPage::populateUsersLists(){
    QList<QString> availableusers = _projDataService.getAvailableUsers(projId);
    QList<QString> currentUsers = _projDataService.getCurrentUsers(projId);
    ui->AvailableUsers->addItems(availableusers);
    ui->CurrentUsers->addItems(currentUsers);
}

void ProjectSettingsPage::createListMenus(){
    auto AssignUser = new QAction("Assign to project", this);
    connect(AssignUser, SIGNAL(triggered()), this, SLOT(addNewUserToTask()));
    ui->AvailableUsers->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->AvailableUsers->addActions({AssignUser});

    auto RemoveUser = new QAction("Remove from project", this);
    connect(RemoveUser, SIGNAL(triggered()), this, SLOT(removeUser()));
    ui->CurrentUsers->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->CurrentUsers->addActions({RemoveUser});
}

void ProjectSettingsPage::addNewUserToTask(){
    QListWidget *list = ui->AvailableUsers;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *user = list->takeItem(list->currentRow());
        ui->CurrentUsers->addItem(user);
    }
}

void ProjectSettingsPage::removeUser(){
    QListWidget *list = ui->CurrentUsers;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *user = list->takeItem(list->currentRow());
        ui->AvailableUsers->addItem(user);
    }
}

void ProjectSettingsPage::onSaveBtnClicked(){
    QString projectTitle = ui->ProjectNameEdit->text();
    QVector<QString> currentUsers;
    for(auto item: ui->CurrentUsers->findItems("*",Qt::MatchWildcard)){
        QString i = item->data(0).toString();
        currentUsers.append(i);
    }
    if(_projDataService.getProjectTitle(projId) == projectTitle){
        // title has not changed
    }
    else{
        if(_projDataService.updateProjectTitle(projId, projectTitle)){
            qDebug() << "Updated the project title";
        }
    }

    if(_projDataService.updateProjectUsers(projId, currentUsers)){
        qDebug() << "Success";
        this->hide();
    }
    else
        qDebug() << "Failed to update users";
}

ProjectSettingsPage::~ProjectSettingsPage()
{
    delete ui;
}
