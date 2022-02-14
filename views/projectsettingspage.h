#ifndef PROJECTSETTINGSPAGE_H
#define PROJECTSETTINGSPAGE_H

#include <QDialog>
#include "services/projectdataservice.h"
#include <QAction>

namespace Ui {
class ProjectSettingsPage;
}

class ProjectSettingsPage : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectSettingsPage(QWidget *parent = nullptr, int projectId = 0);
    ~ProjectSettingsPage();

private:
    Ui::ProjectSettingsPage *ui;
    int projId;
    ProjectDataService _projDataService;

private slots:
    void populateUsersLists();
    void addNewUserToTask();
    void createListMenus();
    void removeUser();
    void onSaveBtnClicked();
};

#endif // PROJECTSETTINGSPAGE_H
