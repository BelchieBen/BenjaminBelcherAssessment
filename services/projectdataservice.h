#ifndef PROJECTDATASERVICE_H
#define PROJECTDATASERVICE_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QIODevice>
#include "models/projectmessage.h"
#include "services/taskdataservice.h"
#include "globals/taskstates.h"
#include "utils/time.h"


class ProjectDataService
{
public:
    ProjectDataService();
    bool createProject(QString title, QString desc, QString status, QString manager);
    bool insertProjUsers(QVector<QString> users, int project);
    int getProject(QString title);
    QString getProjectTitle(int id);
    QList<QString> getProjectUsers(int projectId);
    QList<QString> getAvailableUsers(int projectId);
    QList<QString> getCurrentUsers(int projectId);
    bool updateProjectTitle(int projectId, QString title);
    bool updateProjectUsers(int projId, QVector<QString> currentUsers);
    bool deleteprojectUsers(int projId);
    bool sendProjectMessage(int projId, QString messageTitle, QString messageBody, int uId);
    QList<ProjectMessage> fetchProjectMessages(int projId);
    int calculateProjectProgress(QString projectTitle);

private:
    Time time;
    TaskDataService taskDataService;
    TaskStates states;
};

#endif // PROJECTDATASERVICE_H
