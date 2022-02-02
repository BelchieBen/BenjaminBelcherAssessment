#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>
#include "taskdelegate.h"
#include "newtaskform.h"
#include "newprojectform.h"
#include <QMenu>

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


private slots:
    void onAddTestTaskClicked();
    void openCreateTask();
    void openCreateProject();
    void showContextMenu(const QPoint&);

public slots:
    void loadTasks();
};

#endif // MAINDASHBOARD_H
