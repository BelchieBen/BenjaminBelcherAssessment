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
    /**
    * The constructor takes all the properties as arguments to construct the object
    */
    this->messageId = msgId;
    this->messageTitle = msgTitle;
    this->messageBody = msgBody;
    this->created = crtd;
    this->projectId = projId;
    this->author = authr;

}

int ProjectMessage::getMessageId() const
{
    /**
    * Returns the message ID
    */
    return messageId;
}

 QString ProjectMessage::getMessageTitle()
{
     /**
     * Returns the message title
     */
    return messageTitle;
}

 QString ProjectMessage::getMessageBody()
{
     /**
     * Returns the message content
     */
    return messageBody;
}

 QString ProjectMessage::getCreated()
{
     /**
     * Returns the date & time the message was created
     */
    return created;
}

int ProjectMessage::getProjectId() const
{
    /**
    * Returns the project ID that the message is related to
    */
    return projectId;
}

int ProjectMessage::getAuthor() const
{
    /**
    * Returns the author of the message
    */
    return author;
}
