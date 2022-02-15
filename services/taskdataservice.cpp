#include "taskdataservice.h"



TaskDataService::TaskDataService()
{ 

}


QString getTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string localTime = asctime(localtm);
    QString qTime = QString::fromStdString(localTime);
    return qTime;
}

bool TaskDataService::createTask(QString title, QString desc, QString effort, QString priority, QString project, QString state, QString assingee){
    QSqlQuery q;
    q.prepare( "INSERT INTO tasks (title, description, effort, priority, created, project, state) "
            "VALUES (:tle, :desc, :eff, :pri, :crted, :prj, :ste)");
    q.bindValue(":tle",title );
    q.bindValue(":desc", desc);
    q.bindValue(":eff", effort);
    q.bindValue(":pri", priority);
    q.bindValue(":crted", getTime());
    q.bindValue(":prj", project);
    q.bindValue(":ste", state);
    int userId = usr.getUserId(assingee);

    if(q.exec()){
        if(assingee == "Unassigned"){

        }
        else{
            int taskId = getTaskId(title);
            addUserToTask(taskId, userId);
        }
        return true;
    }
    else{
        qDebug() << q.lastError().text();
        return false;
    }
}

bool TaskDataService::addUserToTask(int taskId, int userId){
    QSqlQuery q;
    QString query = "INSERT OR REPLACE INTO task_users (user_id, task_id) VALUES ("+QString::number(userId)+", "+QString::number(taskId)+")";
//    q.prepare("INSERT INTO task_users (user_id, task_id) VALUES (:uId, :tkId)");
//    q.bindValue("tkId", QString::number(userId));
//    q.bindValue("uId", QString::number(taskId));
    if(q.exec(query)){
        qDebug() << "Added user to task";
        return true;
    }
    else{
        qDebug() << q.lastError().text();
        qDebug() << "Couldnt add user to task";
        return false;
    }
}

int TaskDataService::getTaskId(QString title){
    int id = 0;
    QSqlQuery q;
    QString qry = "SELECT * FROM tasks WHERE tasks.title = '"+title+"'";
//    q.prepare("SELECT * FROM tasks WHERE title = :tle");
//    q.bindValue(":tle", title);
    if(q.exec(qry)){
        while(q.next()){
            id = q.value(0).toInt();
        }
    }
    else
        qDebug() << q.lastError().text();
    return id;
}

bool TaskDataService::updateTaskStatus(QListWidgetItem task, QString state){
    QString titleStr = task.data(0).toString();
    QSqlQuery q;
    q.prepare("UPDATE tasks SET state = :sts WHERE title = :tle");
    q.bindValue(":sts", state);
    q.bindValue(":tle", titleStr);

    if(q.exec()){
        return true;
    }
    else{
        return false;
    }
}

QStringList TaskDataService::populatingAssigneesList(int projectId){
    QStringList assignees;
    assignees.append("Unassigned");
    QString email;
    QSqlQuery q;
    q.prepare("SELECT * FROM project_users WHERE project = :proj");
    q.bindValue(":proj", projectId);
    if(q.exec()){
        while(q.next()){
            email = q.value(1).toString();
            assignees.append(email);
        }
    }
    return assignees;
}

QList<Task> TaskDataService::tasksAssignedToUser(int uId, QString projectTitle){
    QList<Task> taskList;
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks INNER JOIN task_users on tasks.id = task_users.task_id WHERE tasks.project = :proj");
    q.bindValue(":proj", projectTitle);
    if(q.exec()){
        int count = 0;
        while(q.next()){
            Task t = Task(q.value(1).toString(), q.value(2).toString(),q.value(3).toString(),q.value(4).toString(),q.value(5).toString(),q.value(6).toString(),q.value(7).toString(), q.value(8).toInt());
            taskList.append(t);
            count ++;
        }
        if(count == 0){
            qDebug() << "No tasks found for "+QString::number(uId);
        }
        else if(count >= 1){
            qDebug() << "Tasks found for "+QString::number(uId);
        }
    }
    return taskList;
}

QList<Task> TaskDataService::findAllTasksForUser(int uId){
    QList<Task> taskList;
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks INNER JOIN task_users on tasks.id = task_users.task_id WHERE task_users.user_id= :uid");
    q.bindValue(":uid", uId);
    if(q.exec()){
        int count = 0;
        while(q.next()){
            Task t = Task(q.value(1).toString(), q.value(2).toString(),q.value(3).toString(),q.value(4).toString(),q.value(5).toString(),q.value(6).toString(),q.value(7).toString(), q.value(8).toInt());
            taskList.append(t);
            count ++;
        }
        if(count == 0){
            qDebug() << "No tasks found for "+QString::number(uId);
        }
        else if(count >= 1){
            qDebug() << "Tasks found for "+QString::number(uId);
        }
    }
    return taskList;
}

QList<QString> TaskDataService::findProjectsUserIsIn(int uId){
    QList<QString> projects;
    QSqlQuery q;
    q.prepare("SELECT * FROM projects INNER JOIN project_users on projects.id = project_users.project WHERE project_users.user = :usr");
    q.bindValue(":usr", usr.returnEmail(uId));
    if(q.exec()){
        while(q.next()){
            projects.append(q.value(1).toString());
        }
    }
    return projects;
}

Task TaskDataService::findTaskById(int id){
    QSqlQuery q;
    Task t;
    q.prepare("SELECT * FROM tasks INNER JOIN task_users on tasks.id = task_users.task_id WHERE task_users.task_id= :tskId");
    q.bindValue(":tskId", id);
    if(q.exec()){
        while(q.next()){
            t = Task(q.value(1).toString(), q.value(2).toString(),q.value(3).toString(),q.value(4).toString(),q.value(5).toString(),q.value(6).toString(),q.value(7).toString(), q.value(8).toInt());
        }
    }
    return t;
}
