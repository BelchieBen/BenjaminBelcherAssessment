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
#include "globals/projectstates.h"
#include "utils/time.h"

/**
* This class contains all the methods to handle the data opertions required to maintain projects in the application.
*/


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
    bool isProjectNotStarted(int projectId);
    bool updateProjectStatus(int projetId, QString status);
    bool isProjectComplete(int projectId);

private:
    Time time;
    TaskStates states;
    ProjectStates projectStates;
    EmailServerDetails details;
    TaskDataService taskDataService;
};

#endif // PROJECTDATASERVICE_H
