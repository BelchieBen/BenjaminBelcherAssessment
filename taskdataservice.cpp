#include "taskdataservice.h"

QMap<QString, QString> states;

TaskDataService::TaskDataService()
{ 
    states["Todo"] = "Todo";
    states["InProgress"] = "In Progress";
    states["InReview"] = "In Review";
    states["Done"] = "Done";

}


QString getTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string localTime = asctime(localtm);
    QString qTime = QString::fromStdString(localTime);
    return qTime;
}

bool TaskDataService::createTask(QString title, QString desc, QString effort, QString priority, QString project){
    QSqlQuery q;
    q.prepare( "INSERT INTO tasks (title, description, effort, priority, created, project, state) "
            "VALUES (:tle, :desc, :eff, :pri, :crted, :prj, :ste)");
    q.bindValue(":tle",title );
    q.bindValue(":desc", desc);
    q.bindValue(":eff", effort);
    q.bindValue(":pri", priority);
    q.bindValue(":crted", getTime());
    q.bindValue(":prj", "Test Project");
    q.bindValue(":ste", states["Todo"]);

    if(q.exec()){
        return true;
    }
    else
        return false;
}

bool TaskDataService::updateTaskStatus(QListWidgetItem task){
    QString titleStr = task.data(0).toString();
    QSqlQuery q;
    q.prepare("UPDATE tasks SET state = :sts WHERE title = :tle");
    q.bindValue(":sts", states["InProgress"]);
    q.bindValue(":tle", titleStr);

    if(q.exec()){
        return true;
    }
    else{
        return false;
    }
}
