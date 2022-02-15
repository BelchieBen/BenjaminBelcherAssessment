#ifndef TASKDETAILS_H
#define TASKDETAILS_H

#include <QDialog>
#include <QListWidgetItem>
#include "services/taskdataservice.h"

namespace Ui {
class TaskDetails;
}

class TaskDetails : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDetails(QWidget *parent = nullptr, QListWidgetItem *item = nullptr);
    ~TaskDetails();

private:
    Ui::TaskDetails *ui;
    QListWidgetItem *task;
    TaskDataService _taskDataService;

private slots:
    void populateTaskDetails();
};

#endif // TASKDETAILS_H
