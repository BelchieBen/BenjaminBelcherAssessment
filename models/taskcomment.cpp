#include "taskcomment.h"

TaskComment::TaskComment(
        int cmtId,
        int tkId,
        QString cmt,
        QDateTime dte,
        int uId
)
{
    this->commentId = cmtId;
    this->task_id = tkId;
    this->comment = cmt;
    this->posted = dte;
    this->userId = uId;
}

int TaskComment::getCommentId() const
{
    return commentId;
}

int TaskComment::getTask_id() const
{
    return task_id;
}

QString TaskComment::getComment()
{
    return comment;
}

 QDateTime TaskComment::getPosted()
{
     return posted;
 }

 int TaskComment::getUserId() const
 {
     return userId;
 }
