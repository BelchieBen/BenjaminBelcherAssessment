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
}

void ProjectSettingsPage::populateUsersLists(){
    QList<QString> availableusers = _projDataService.getAvailableUsers(projId);
    ui->AvailableUsers->addItems(availableusers);
}

ProjectSettingsPage::~ProjectSettingsPage()
{
    delete ui;
}
