#ifndef TASKSTATES_H
#define TASKSTATES_H
#include <QString>
#include <QMap>

/**
* This class holds the different states for the tasks, the value of each state won't change throughout the application's lifecycle so it makes sense to store them in a single place
* to improve the applications integrity and efficiency
*/

class TaskStates
{
public:
    TaskStates();
    QMap<QString, QString> states;
    QString TodoState();
    QString InProgressState();
    QString InReviewState();
    QString InDoneState();
};

#endif // TASKSTATES_H
