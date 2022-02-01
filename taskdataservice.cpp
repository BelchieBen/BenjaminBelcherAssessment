#include "taskdataservice.h"

TaskDataService::TaskDataService()
{

}

enum states{
    Todo = 0,
    InProgress = 1,
    Review = 2,
    Complete = 3,
};

QString getTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string localTime = asctime(localtm);
    QString qTime = QString::fromStdString(localTime);
    return qTime;
}

bool TaskDataService::createTask(QString title, QString desc, QString effort, QString priority, QString project){
    QString stateStr = QVariant::fromValue(states::Todo).toString();
    QSqlQuery q;
    q.prepare( "INSERT INTO tasks (title, description, effort, priority, created, project, state) "
            "VALUES (:tle, :desc, :eff, :pri, :crted, :prj, :ste)");
    q.bindValue(":tle",title );
    q.bindValue(":desc", desc);
    q.bindValue(":eff", effort);
    q.bindValue(":pri", priority);
    q.bindValue(":crted", getTime());
    q.bindValue(":prj", "Test Project");
    q.bindValue(":state", stateStr);

    if(q.exec()){
        qDebug() << "Added Task";
        return true;
    }
    else
        return false;
}
