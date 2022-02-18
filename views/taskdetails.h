#ifndef TASKDETAILS_H
#define TASKDETAILS_H

#include <QDialog>
#include <QListWidgetItem>
#include "services/taskdataservice.h"
#include "delegates/commentdelegate.h"
#include "models/user.h"

namespace Ui {
class TaskDetails;
}

class TaskDetails : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDetails(QWidget *parent = nullptr, QListWidgetItem *item = nullptr);
    explicit TaskDetails(QWidget *parent = nullptr, Task *item = nullptr);
    ~TaskDetails();

private:
    Ui::TaskDetails *ui;
    QListWidgetItem *task;
    Task *taskT;
    TaskDataService _taskDataService;
    int taskId;
    QMessageBox _messageBox;
    user usr;

private slots:
    void populateTaskDetails();
    void addCommentToTask();
    void populateCommentBox();
    void populateTaskDetailsUsingModel();
};

#endif // TASKDETAILS_H
