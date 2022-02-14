#include "projectdataservice.h"

ProjectDataService::ProjectDataService()
{

}

int ProjectDataService::getProject(QString title){
    QSqlQuery q;
    q.prepare("SELECT * from projects WHERE title = :tle");
    q.bindValue(":tle", title);
    if(q.exec()){
        int projectId;
        while(q.next()){
            projectId = q.value(0).toInt();
        }
        return projectId;
    }
    else
        return 0;
}

bool ProjectDataService::insertProjUsers(QVector<QString> users, int project){
    QVector<QString>::iterator loop;
    for(loop = users.begin(); loop != users.end(); loop++){
        QSqlQuery q;
        q.prepare("INSERT INTO project_users (user, project) "
                  "VALUES (:usr, :prj)");
        q.bindValue(":usr", *loop);
        q.bindValue(":prj", project);

        if(q.exec()){
            qDebug() << "Added user";
        }
    }
    return true;
}

bool ProjectDataService::createProject(QString title, QString desc, QString status, QString manager){
    QSqlQuery q;
    q.prepare("INSERT INTO projects (title, description, status, manager) "
              "VALUES (:tle, :descrip, :stat, :mgr)");
    q.bindValue(":tle", title);
    q.bindValue(":descrip", desc);
    q.bindValue(":stat", status);
    q.bindValue(":mgr", manager);

    if(q.exec()){
        getProject(title);
        return true;
    }
    else{
        qDebug() << q.lastError().text();
        return false;
    }
}

QString ProjectDataService::getProjectTitle(int id){
    QSqlQuery q;
    q.prepare("SELECT * FROM projects WHERE id = :id");
    q.bindValue(":id", id);
    if(q.exec()){
        QString title;
        while(q.next()){
            title = q.value(1).toString();
        }
        return title;
    }
    else
        return "";
}

QList<QString> ProjectDataService::getProjectUsers(int projectId){
    QString email;
    QList<QString> users;
    QSqlQuery q;
    q.prepare("SELECT * FROM project_users WHERE project = :proj");
    q.bindValue(":proj", projectId);
    if(q.exec()){
        while(q.next()){
            email = q.value(1).toString();
            users.append(email);
        }
    }
    return users;
}

QList<QString> ProjectDataService::getAvailableUsers(int projectId){
    QString email, availableUsrEml;
    QList<QString> users;
    QSqlQuery q, qry;
    q.prepare("SELECT users.email FROM users LEFT JOIN project_users on users.email = project_users.user EXCEPT SELECT users.email FROM users LEFT JOIN project_users on users.email = project_users.user WHERE project_users.project = :projId");
    q.bindValue(":projId", projectId);
    if(q.exec()){
        while(q.next()){
            email = q.value(0).toString();
            users.append(email);
        }
    }
    qDebug() << users;
    return users;
}

QList<QString> ProjectDataService::getCurrentUsers(int projectId){
    QList<QString> users;
    QSqlQuery q;
    q.prepare("SELECT * FROM project_users WHERE project = :proj");
    q.bindValue(":proj", projectId);
    if(q.exec()){
        while(q.next()){
            users.append(q.value(1).toString());
        }
    }
    return users;
}

bool ProjectDataService::updateProjectTitle(int projectId, QString title){
    QSqlQuery q;
    q.prepare("UPDATE projects SET title = :tle WHERE id = :id");
    q.bindValue(":tle", title);
    q.bindValue(":id", projectId);
    if(q.exec()){
        return true;
    }
    else{
        return false;
    }
}

bool ProjectDataService::deleteprojectUsers(int projId){
    QSqlQuery q;
    q.prepare("DELETE FROM project_users WHERE project = :proj");
    q.bindValue(":proj", projId);
    if(q.exec()){
        qDebug() << "Removed old users";
        return true;
    }
    return false;
}

bool ProjectDataService::updateProjectUsers(int projId, QVector<QString> currentUsers){
    if(deleteprojectUsers(projId)){
        if(insertProjUsers(currentUsers, projId)){
            return true;
        }
    }
    else{
        return false;
    }
}
