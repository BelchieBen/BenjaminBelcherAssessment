#ifndef TASKCOMMENT_H
#define TASKCOMMENT_H

#include <QString>
#include <QDateTime>

/**
* This class is the model for comments left on a task and holds all the relevent infomation about a comment
*/

class TaskComment
{
public:
    TaskComment(
            int commentId,
            int task_id,
            QString comment,
            QDateTime posted,
            int uId
            );
    int getCommentId() const;

    int getTask_id() const;

     QString getComment();

     QDateTime getPosted();

     int getUserId() const;

private:
    int commentId;
    int task_id;
    QString comment;
    QDateTime posted;
    int userId;
};

#endif // TASKCOMMENT_H
