#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task();
    Task(QString title, QString desc, QString effort, QString priority, QString created, QString project, QString state, int userId);
    QString returnTitle();
    QString returnDescription();
    QString returnEffort();
    QString returnPriority();
    QString returnCreated();
    QString returnProject();
    QString returnState();
    int returnUser();

private:
    QString title, description, effort, priority, created, project, state;
    int userId;
};


#endif // TASK_H
