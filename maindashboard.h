#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>
#include "taskdelegate.h"
#include "newtaskform.h"
#include "newprojectform.h"
#include <QMenu>
#include <QListWidget>

namespace Ui {
class MainDashboard;
}

class MainDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit MainDashboard(QWidget *parent = nullptr);
    ~MainDashboard();

private:
    Ui::MainDashboard *ui;
    NewTaskForm newTask;
    NewProjectForm newProject;

    QListWidget *taskList;
    QListWidget *inProgress;;


private slots:
    void onAddTestTaskClicked();
    void openCreateTask();
    void openCreateProject();
    void showContextMenu(const QPoint&);
    void showInProgressMenu(const QPoint&);
    void moveTask();
    void populateLists(QString state, QString title, QString description);
    void clearLists();

public slots:
    void loadTasks();

signals:
    void movedItem();
};

#endif // MAINDASHBOARD_H
