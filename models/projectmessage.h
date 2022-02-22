#ifndef PROJECTMESSAGE_H
#define PROJECTMESSAGE_H

#include <QString>
#include <QDateTime>

/**
* This class is a model for a project message, the project message is what appears on the project timeline
*/

class ProjectMessage
{
public:
    ProjectMessage(
            int messageId,
            QString messageTitle,
            QString messageBody,
            QString created,
            int projectId,
            int author
            );

    int getMessageId() const;
    QString getMessageTitle() ;
    QString getMessageBody() ;
    QString getCreated() ;
    int getProjectId() const;
    int getAuthor() const;

private:
    int messageId;
    QString messageTitle;
    QString messageBody;
    QString created;
    int projectId;
    int author;
};

#endif // PROJECTMESSAGE_H
