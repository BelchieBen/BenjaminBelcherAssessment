#ifndef PROJECTDATASERVICE_H
#define PROJECTDATASERVICE_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QIODevice>


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
};

#endif // PROJECTDATASERVICE_H
