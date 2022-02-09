#ifndef TASKDATASERVICE_H
#define TASKDATASERVICE_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <ctime>
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>
#include <QListWidgetItem>
#include "models/user.h"


class TaskDataService
{
public:
    TaskDataService();
    bool createTask(QString title, QString desc, QString effort, QString priority, QString project, QString state, QString assignee);
    bool updateTaskStatus(QListWidgetItem task, QString state);
    bool addUserToTask(int taskId, int userId);
    int getTaskId(QString title);
    QStringList populatingAssigneesList();

private:
    user usr;
};

#endif // TASKDATASERVICE_H
