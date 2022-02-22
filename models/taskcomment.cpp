#include "taskcomment.h"

TaskComment::TaskComment(
        int cmtId,
        int tkId,
        QString cmt,
        QDateTime dte,
        int uId
)
{
    /**
    * The constructor assigns all the arguments to the class properties and constructs the object
    */
    this->commentId = cmtId;
    this->task_id = tkId;
    this->comment = cmt;
    this->posted = dte;
    this->userId = uId;
}

int TaskComment::getCommentId() const
{
    /**
    * Returns the comment ID
    */
    return commentId;
}

int TaskComment::getTask_id() const
{
    /**
    * Returns the task ID that the comment is placed on
    */
    return task_id;
}

QString TaskComment::getComment()
{
    /**
    * Returns the comment content
    */
    return comment;
}

 QDateTime TaskComment::getPosted()
{
     /**
     * Returns the comment's date posted
     */
     return posted;
 }

 int TaskComment::getUserId() const
 {
     /**
     * Returns the user ID who posted the comment
     */
     return userId;
 }
