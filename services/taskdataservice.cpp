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
    int taskId = getTaskId(title);
    addUserToTask(taskId, userId);

    if(q.exec()){
        return true;
    }
    else{
        qDebug() << q.lastError().text();
        return false;
    }
}

bool TaskDataService::addUserToTask(int taskId, int userId){
    QSqlQuery q;
    QString query = "INSERT INTO task_users (user_id, task_id) VALUES ("+QString::number(userId)+", "+QString::number(taskId)+")";
//    q.prepare("INSERT INTO task_users (user_id, task_id) VALUES (:uId, :tkId)");
//    q.bindValue("tkId", QString::number(userId));
//    q.bindValue("uId", QString::number(taskId));
    if(q.exec(query)){
        qDebug() << "Added user to task";
        return true;
    }
    else{
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

QStringList TaskDataService::populatingAssigneesList(){
    QStringList assignees;
    QString email;
    QSqlQuery q;
    q.prepare("SELECT * FROM users");
    if(q.exec()){
        while(q.next()){
            email = q.value(3).toString();
            assignees.append(email);
        }
    }
    return assignees;
}
