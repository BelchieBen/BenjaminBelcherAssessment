#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>
#include "delegates/taskdelegate.h"
#include "views/forms/newtaskform.h"
#include "views/forms/newprojectform.h"
#include <QMenu>
#include <QListWidget>
#include "globals/taskstates.h"
#include <QTreeWidget>
#include "services/projectdataservice.h"
#include "views/loginlandingpage.h"
#include "services/taskdataservice.h"
#include "models/user.h"
#include "globals/userroles.h"

namespace Ui {
class MainDashboard;
}

class MainDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit MainDashboard(QWidget *parent = nullptr, int projectId = 0);
    ~MainDashboard();

private:
    Ui::MainDashboard *ui;
    int projId;
    NewTaskForm newTask;
    NewProjectForm newProject;
    TaskStates taskStates;
    ProjectDataService _projDataService;
    user usr;
    UserRoles roles;


private slots:
    void onAddTestTaskClicked();
    void openCreateTask();
    void openCreateProject();
    void createListMenus();
    void moveTaskToInProgress();
    void moveTaskToReview();
    void moveTaskToDone();
    void populateLists(QString state, QString title, QString description);
    void clearLists();
    void searchCurrentBoard();
    void openProjectsDialog();
    void openProjectSettings();
    void createManagerBtns();

    void on_SearchCurrentBoard_textChanged(const QString &arg1);

public slots:
    void loadTasks();

signals:
    void movedItem();
};

#endif // MAINDASHBOARD_H
