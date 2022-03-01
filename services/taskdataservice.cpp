#include "taskdataservice.h"



TaskDataService::TaskDataService()
{ 

}

bool TaskDataService::createTask(QString title, QString desc, QString effort, QString priority, QString project, QString state, QString assingee){
    /**
    * This method inserts a task into the database and takes every field from the UI form as an argument. If the task was inserted successfully then the method will return true.
    */
    QSqlQuery q;
    q.prepare( "INSERT INTO tasks (title, description, effort, priority, created, project, state) "
            "VALUES (:tle, :desc, :eff, :pri, :crted, :prj, :ste)");
    q.bindValue(":tle",title );
    q.bindValue(":desc", desc);
    q.bindValue(":eff", effort);
    q.bindValue(":pri", priority);
    q.bindValue(":crted", time.getCurrentTime());
    q.bindValue(":prj", project);
    q.bindValue(":ste", state);
    int userId = usr.getUserId(assingee);

    if(q.exec()){
        if(assingee == "Unassigned"){

        }
        else{
            int taskId = getTaskId(title);
            addUserToTask(taskId, userId);
            EmailService* smtp = new EmailService(details.getUsername(), details.getPassword(), details.getServerAddress(), details.getPort());
            smtp->sendMail(details.getUsername(), assingee, "You have been assigned to a task!", title);
        }
        return true;
    }
    else{
        qDebug() << q.lastError().text();
        return false;
    }
}

bool TaskDataService::addUserToTask(int taskId, int userId){
    /**
    * This method addds a user to a task by inserting thier User ID and the Task ID into a table called task_users. If the user could be inserted to the database then the method
    * would return true.
    */
    QSqlQuery q;
    QString query = "INSERT OR REPLACE INTO task_users (user_id, task_id) VALUES ("+QString::number(userId)+", "+QString::number(taskId)+")";
    QString email = usr.returnEmail(userId);
    Task t = findTaskById(taskId);
    QString taskT = t.returnTitle();
    if(q.exec(query)){
        qDebug() << "Added user to task";
        EmailService* smtp = new EmailService(details.getUsername(), details.getPassword(), details.getServerAddress(), details.getPort());
        smtp->sendMail(details.getUsername(), email, "You have been assigned to a task!", "The task you have been assigned is "+taskT);
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
    /**
    * This method updates the status of a task when it is moved. The first argument is a QListWidgetItem and that is the task, the second argument is the new state of the task.
    */
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
    /**
    * This method populates the list that displays all of the users assigned to a project. That project is determined by the Project ID argument. This method returns a QStringList
    * of all the users email's.
    */
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
    /**
    * This method returns a QList of tasks that a user is assigned to within a specific project. To use this method a User ID and Project Title must be specified in the arguments. If the user has any tasks
    * assigned to them, a list of Task objects will be returned.
    */
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
    /**
    * This method returns a QList of Tasks that a user has assigned to them, reguardless of project. To use this method a User ID must be specified in the arguments.
    * If the user has any tasks assigned to them, a list of Task objects will be returned.
    */
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
    /**
    * This method returns a QList of project title's and these are all the projects a user is assigned to. The only argument is a User ID.
    */
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
    /**
    * This method returns a Task object that is associated with a given Task ID in the database. This method is used when only a Task ID is known but more infomation about a task is needed.
    */
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

bool TaskDataService::addCommentToTask(QString comment, int taskId){
    /**
    * This method inserts a comment to the task_comments table in the database, if the comment is added successfully then the method will return true.
    */
    QSqlQuery q;
    user u = usr.getCurrentUser();
    q.prepare("INSERT INTO task_comments (task_id, comment, date_created, author) VALUES (:tkId, :cmt, :created, :usr)");
    q.bindValue(":tkId", taskId);
    q.bindValue(":cmt", comment);
    q.bindValue(":created", time.getCurrentTime());
    q.bindValue(":usr", usr.getUserId(u.GetCurrentUserEmail()));
    if(q.exec()){
        qDebug() << "Added comment to task "+QString::number(taskId);
        return true;
    }
    return false;

}

QList<TaskComment> TaskDataService::getTaskComments(int TaskId){
    /**
    * This method gets all the comments added to a given task, this method returns a QList of TaskComment's.
    */
    QSqlQuery q;
    QDateTime qDt;
    QList<TaskComment> comments;
    q.prepare("SELECT * FROM task_comments WHERE task_id = :tkId");
    q.bindValue(":tkId", TaskId);
    if(q.exec()){
        int count = 0;
        while(q.next()){
            qDt = QDateTime::fromString(q.value(3).toString());
            TaskComment comment = TaskComment(q.value(0).toInt(), q.value(1).toInt(), q.value(2).toString(),qDt, q.value(4).toInt());
            comments.append(comment);
            count ++;
        }
        if(count == 0){
            qDebug() << "No comments for "+QString::number(TaskId);
        }
        else{
            qDebug()<< QString::number(count)+" comments where found for "+QString::number(TaskId);
        }
    }
    return comments;
}

QList<Task> TaskDataService::fetchProjectTasks(QString projectTitle){
    /**
    * This method gets all the tasks in a given project which is determined by the Project Title argument, these tasks are returned as a QList.
    */
    QSqlQuery q;
    QList<Task> tasks;
    q.prepare("SELECT * FROM tasks WHERE project = :proj");
    q.bindValue(":proj", projectTitle);
    if(q.exec()){
        while(q.next()){
            Task task = Task(q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toString(), q.value(5).toString(),q.value(6).toString(), q.value(7).toString(), q.value(8).toInt());
            tasks.append(task);
        }
    }
    return tasks;
}

QList<Task> TaskDataService::fetchAllTasks(QString search){
    /**
    * This method gets all the tasks from the database that match the search passed in as an argument. These tasks are returned as a QList.
    */
    QList<Task> tasks;
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks WHERE title = :tle");
    q.bindValue(":tle", search);
    if(q.exec()){
        while(q.next()){
            Task t = Task(q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toString(), q.value(5).toString(),q.value(6).toString(), q.value(7).toString(), q.value(8).toInt());
            tasks.append(t);
        }
    }
    return tasks;
}

bool TaskDataService::removeTaskAssignee(int taskId)
{
    QSqlQuery q;
    q.prepare("UPDATE task_users SET user_id = NULL WHERE task_id = :id");
    q.bindValue(":id", taskId);
    if(q.exec()){
        qDebug()<<"Unassigned user from task";
        return true;
    }
    return false;
}

bool TaskDataService::updateTaskDetails(int taskId, QString priority, QString effort, QString description)
{
    QSqlQuery q;
    q.prepare("UPDATE tasks SET description = :dsc, effort = :efrt, priority = :prty WHERE id = :id");
    q.bindValue(":dsc", description);
    q.bindValue(":efrt", effort);
    q.bindValue(":prty", priority);
    q.bindValue(":id", taskId);
    if(q.exec()){
        qDebug() << "Updated task details";
        return true;
    }
    return false;
}
