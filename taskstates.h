#ifndef TASKSTATES_H
#define TASKSTATES_H
#include <QString>
#include <QMap>

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
