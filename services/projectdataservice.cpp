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
    QString title = getProjectTitle(project);
    QVector<QString>::iterator loop;
    for(loop = users.begin(); loop != users.end(); loop++){
        QSqlQuery q;
        q.prepare("INSERT INTO project_users (user, project) "
                  "VALUES (:usr, :prj)");
        q.bindValue(":usr", *loop);
        q.bindValue(":prj", project);

        if(q.exec()){
            qDebug() << "Added user";
            EmailService* smtp = new EmailService(details.getUsername(), details.getPassword(), details.getServerAddress(), details.getPort());
            smtp->sendMail(details.getUsername(), *loop, "You have been assigned to a project!", "The project you have been assigned to is: "+title);
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

bool ProjectDataService::sendProjectMessage(int projId, QString messageTitle, QString messageBody, int uId){
    QSqlQuery q;
    //QString qry = "INSERT INTO project_messages (title, body, created, project, user) VALUES ('"+messageTitle+"', '"+messageBody+"', '"+time.getCurrentTime()+"', '"+QString::number(projId)+"', '"+QString::number(uId)+"')";
    q.prepare("INSERT INTO project_messages (title, body, created, project, user) VALUES (:tle, :bdy, :crtd, :projId, :uId)");
    q.bindValue(":tle", messageTitle);
    q.bindValue(":bdy", messageBody);
    q.bindValue(":crtd", time.getCurrentTime());
    q.bindValue(":projId", QString::number(projId));
    q.bindValue(":uId", QString::number(uId));
    if(q.exec()){
        return true;
    }
    else{
        qDebug() << q.lastError().text();
    }
    return false;
}

QList<ProjectMessage> ProjectDataService::fetchProjectMessages(int projId){
    QList<ProjectMessage> messages;
    QSqlQuery q;
    q.prepare("SELECT * FROM project_messages WHERE project = :projId");
    q.bindValue(":projId", projId);
    if(q.exec()){
        while(q.next()){
            ProjectMessage message = ProjectMessage(q.value(0).toInt(), q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toInt(), q.value(5).toInt());
            messages.append(message);
        }
    }
    return messages;
}

int ProjectDataService::calculateProjectProgress(QString projectTitle){
    QList<Task> tasksInProject = taskDataService.fetchProjectTasks(projectTitle);
    QList<Task>::iterator i;
    int todo = 0;
    int progress = 0;
    int review = 0;
    int done = 0;
    for(i = tasksInProject.begin(); i != tasksInProject.end(); ++i){
        if(i->returnState() == states.TodoState()){
            todo++;
        }
        if(i->returnState() == states.InProgressState()){
            progress++;
        }
        if(i->returnState() == states.InReviewState()){
            review++;
        }
        if(i->returnState() == states.InDoneState()){
            done++;
        }
    }
    int taskDonePercentage = 0;

    if(done != 0){
        int totalTasks = todo+progress+review+done;
        taskDonePercentage =  done*100 /totalTasks;
    }

    return taskDonePercentage;
}
