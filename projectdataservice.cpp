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
    //QString query = "INSERT INTO projects (title, description, status, manager) VALUES ('"+title+"', '"+desc+"', '"+status+"', '"+manager+"')";
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
