#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>
#include "taskdelegate.h"
#include "newtaskform.h"
#include "newprojectform.h"
#include <QMenu>
#include <QListWidget>
#include "taskstates.h"
#include <QTreeWidget>
#include "projectdataservice.h"
#include "loginlandingpage.h"

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
    void loadListsFromSearch();
    void openProjectsDialog();

public slots:
    void loadTasks();

signals:
    void movedItem();
};

#endif // MAINDASHBOARD_H
