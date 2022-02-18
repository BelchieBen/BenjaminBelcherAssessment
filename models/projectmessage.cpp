#include "projectmessage.h"

ProjectMessage::ProjectMessage(
        int msgId,
        QString msgTitle,
        QString msgBody,
        QString crtd,
        int projId,
        int authr
        )
{
    this->messageId = msgId;
    this->messageTitle = msgTitle;
    this->messageBody = msgBody;
    this->created = crtd;
    this->projectId = projId;
    this->author = authr;

}

int ProjectMessage::getMessageId() const
{
    return messageId;
}

 QString ProjectMessage::getMessageTitle()
{
    return messageTitle;
}

 QString ProjectMessage::getMessageBody()
{
    return messageBody;
}

 QString ProjectMessage::getCreated()
{
    return created;
}

int ProjectMessage::getProjectId() const
{
    return projectId;
}

int ProjectMessage::getAuthor() const
{
    return author;
}
