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
    q.prepare("SELECT * FROM project_users WHERE project = :proj");
    q.bindValue(":proj", projectId);
    if(q.exec()){
        while(q.next()){
            email = q.value(1).toString();
        }

        qry.prepare("SELECT * FROM users EXCEPT SELECT * FROM users WHERE email = :eml");
        qry.bindValue(":eml", email);
        if(qry.exec()){
            availableUsrEml = qry.value(3).toString();
            users.append(availableUsrEml);
        }

    }
    qDebug() << users;
    return users;
}
