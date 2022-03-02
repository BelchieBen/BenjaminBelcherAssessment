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
#include "views/projectsettingspage.h"
#include "services/taskdataservice.h"
#include "views/profile.h"
#include "views/taskdetails.h"
#include "views/projectchat.h"
#include "views/searchtasksallprojectsdialog.h"

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
    NewProjectForm newProject;
    TaskStates taskStates;
    ProjectDataService _projDataService;
    TaskDataService _taskDataService;
    user usr;
    UserRoles roles;
    QMessageBox _messageBox;
    Profile profile;
    ProjectChat *chatroom;
    ProjectStates projectStates;
    QPushButton *CreateTask;
    QPushButton *CreateProjectBtn;


private slots:
    void onAddTestTaskClicked();
    void openCreateTask();
    void openCreateProject();
    void createListMenus();
    void moveTaskToInProgress();
    void moveTaskToReview();
    void moveTaskToDone();
    void populateLists(QString state, QString title, QString description, QString user);
    void clearLists();
    void searchCurrentBoard();
    void openProjectsDialog();
    void openProjectSettings();
    void createManagerBtns();
    void assignToMe();
    void openProfilePage();
    void openProjectChat();
    void returnToMainDashboardFromPages();
    void logoutUser();
    void openTaskDetails(QListWidgetItem *item);
    void unassignFromProgress();
    void unassignFromReview();
    void handleProjectComplete();

    void on_SearchCurrentBoard_textChanged(const QString &arg1);

    void on_TaskList_itemDoubleClicked(QListWidgetItem *item);

    void on_InProgressList_itemDoubleClicked(QListWidgetItem *item);

    void on_ReviewList_itemDoubleClicked(QListWidgetItem *item);

    void on_DoneList_itemDoubleClicked(QListWidgetItem *item);

    void searchAllProjectsForTasks();

public slots:
    void loadTasks();

signals:
    void movedItem();
    void loadProfilePage(user u);
};

#endif // MAINDASHBOARD_H
