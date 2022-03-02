#include "projectdataservice.h"

ProjectDataService::ProjectDataService()
{

}

int ProjectDataService::getProject(QString title){
    /**
    * This method returns the project ID associated to a given title.
    */
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
    /**
    * This method inserts a list of users into the database that are assigned to a project. The arguments this method takes are a QVector of type QString which is thier email
    * and then a project ID. \n The method will return true if all the users where inserted correctly to the database.
    */
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
    /**
    * This method inserts a project into the database and takes several arguments. If the project was inserted successfully then the method will return true.
    */
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
    /**
    * This method returns the title of a given project ID, determined by the argument. The method will query the projects table for a project matching a given ID and then if
    * a project is found the method will return that projects title as a QString.
    */
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
    /**
    * This method returns a QList of users emails determined by the ID of a project passed in as an argument.
    */
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
    /**
    * This method returns a QList of users email's that are not alredy in a project, specified by the argument. If there are users that are not already assigned to a given project
    * then this method will return those.
    */
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
    /**
    * This method returns a QList of users emails determined by the ID of a project passed in as an argument.
    */
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
    /**
    * This method updates the project title stored in the database to the value passed to the second argument, the first argument is the project that is being updated. If the
    * update was successful then the method would return true.
    */
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
    /**
    * This method deletes all the users assigned to a project. If all the users where deleted then the method would return true.
    */
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
    /**
    * This method updates the current users assigned to a project, it takes two arguments. A project ID and a QVector of users to assign.
    */
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
    /**
    * This method is responsible for adding messages from the project timeline to the database. It takes in several arguments which are derived from the fields in the UI. \n
    * If the message is inserted to the database then this method will return true.
    */
    QSqlQuery q;
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
    /**
    * This method returns a QList of type ProjectMessage and these are all the messages associated with a project. The project is determined by the project ID argument. If there are
    * no messages associated with a project then an empty list will be returned.
    */
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
    /**
    * This method calculates the percentage completion of a project, the only argument is the project title and that is used to query the database to find all the tasks
    * associated with the project. \n
    * Then to calculate the completion percentage the total number of tasks completed is divided by the total number of tasks in the project, then this value is multiplied
    * by 100. \n This method will always return a value, if there are no tasks completed then 0 will be returned.
    */
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

bool ProjectDataService::isProjectNotStarted(int projectId)
{
    QString state;
    QSqlQuery q;
    q.prepare("SELECT * from projects WHERE id = :id");
    q.bindValue(":id", projectId);
    if(q.exec()){
        while(q.next()){
            state = q.value(3).toString();
            if(state == projectStates.getState("NotStarted")){
                return true;
            }
        }
    }
    return false;
}

bool ProjectDataService::updateProjectStatus(int projetId, QString status)
{
    QSqlQuery q;
    q.prepare("UPDATE projects SET status = :stus WHERE id = :id");
    q.bindValue(":id", projetId);
    q.bindValue(":stus", status);
    if(q.exec()){
        qDebug() << "Project status updated";
        return true;
    }
    else{
        qDebug() << "Project status not changed";
        qDebug() << q.lastError().text();
        return false;
    }
    return false;
}

bool ProjectDataService::isProjectComplete(int projectId)
{
    QSqlQuery q;
    q.prepare("SELECT status FROM projects WHERE id = :id");
    q.bindValue(":id", projectId);
    if(q.exec()){
        while(q.next()){
            if(q.value(0).toString() == projectStates.getState("Completed")){
                return true;
            }
        }
    }
    return false;
}
