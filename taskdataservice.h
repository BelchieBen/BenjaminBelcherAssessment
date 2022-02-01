#ifndef TASKDATASERVICE_H
#define TASKDATASERVICE_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <ctime>
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>


class TaskDataService
{
public:
    TaskDataService();
    bool createTask(QString title, QString desc, QString effort, QString priority, QString project);
};

#endif // TASKDATASERVICE_H
