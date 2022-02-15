#include "task.h"

Task::Task()
{

}

Task::Task(QString tlr, QString desc, QString eff, QString pri, QString crtd, QString proj, QString ste, int urId){
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
    return this->title;
}

QString Task::returnDescription(){
    return this->description;
}

QString Task::returnEffort(){
    return this->effort;
}

QString Task::returnPriority(){
    return this->priority;
}

QString Task::returnCreated(){
    return this->created;
}

QString Task::returnProject(){
    return this->project;
}

QString Task::returnState(){
    return this->state;
}

int Task::returnUser(){
    return this->userId;
}
