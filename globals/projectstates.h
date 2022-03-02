#ifndef PROJECTSTATES_H
#define PROJECTSTATES_H

#include <QString>
#include <QMap>

class ProjectStates
{
public:
    ProjectStates();
    QMap<QString, QString> states;
    QString getState(QString role);
};

#endif // PROJECTSTATES_H
