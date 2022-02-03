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


class TaskDataService
{
public:
    TaskDataService();
    bool createTask(QString title, QString desc, QString effort, QString priority, QString project);
    bool updateTaskStatus(QListWidgetItem task);
};

#endif // TASKDATASERVICE_H
