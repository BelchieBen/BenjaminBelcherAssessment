#include "task.h"

Task::Task()
{

}

Task::Task(QString tlr, QString desc, QString eff, QString pri, QString crtd, QString proj, QString ste, int urId){
    /**
    * The constructor assigns all the paramaters to the class properties and creates the task object
    */
    this->title = tlr;
    this->description = desc;
    this->effort = eff;
    this->priority = pri;
    this->created = crtd;
    this->project = proj;
    this->state = ste;
    this->userId = urId;
}

QString Task::returnTitle(){
    /**
    * Returns the task title
    */
    return this->title;
}

QString Task::returnDescription(){
    /**
    * Returns the task description
    */
    return this->description;
}

QString Task::returnEffort(){
    /**
    * Returns the task effort
    */
    return this->effort;
}

QString Task::returnPriority(){
    /**
    * Returns the task priority
    */
    return this->priority;
}

QString Task::returnCreated(){
    /**
    * Returns the time the task was created
    */
    return this->created;
}

QString Task::returnProject(){
    /**
    * Returns the project the task is in
    */
    return this->project;
}

QString Task::returnState(){
    /**
    * Returns the task state
    */
    return this->state;
}

int Task::returnUser(){
    /**
    * Returns the user assigned to the task
    */
    return this->userId;
}
