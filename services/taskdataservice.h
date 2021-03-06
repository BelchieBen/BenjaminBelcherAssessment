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
#include "models/task.h"
#include <QDateTime>
#include "models/taskcomment.h"
#include "utils/time.h"
#include "emailservice.h"
#include "globals/emailserverdetails.h"

/**
* This class is responsible for managing all the data operations that are required to create and maintain tasks.
*/

class TaskDataService
{
public:
    TaskDataService();
    bool createTask(QString title, QString desc, QString effort, QString priority, QString project, QString state, QString assignee);
    bool updateTaskStatus(QListWidgetItem task, QString state);
    bool addUserToTask(int taskId, int userId);
    int getTaskId(QString title);
    QStringList populatingAssigneesList(int projectId);
    QList<Task> tasksAssignedToUser(int uId, QString projectTitle);
    QList<Task> findAllTasksForUser(int uId);
    QList<QString> findProjectsUserIsIn(int uId);
    Task findTaskById(int id);
    bool addCommentToTask(QString comment, int taskId);
    QList<TaskComment> getTaskComments(int taskId);
    QList<Task> fetchProjectTasks(QString projectTitle);
    QList<Task> fetchAllTasks(QString search);
    bool removeTaskAssignee(int taskId);
    bool updateTaskDetails(int taskId, QString priority, QString effort, QString description);

private:
    user usr;
    Time time;
    EmailServerDetails details;
};

#endif // TASKDATASERVICE_H
