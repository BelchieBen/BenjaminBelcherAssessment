#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

/**
 * This class inherits from QAbstractItemDelegate which provides the interface to display and edit data items from a model, however I dont use a mode, instead I use a built in method for the QListWidget called SetItemDelegate and that handles most of the configuration for me. \n
 * This class provides the methods to style the tasks shown on the project dashboard in a QListWidget to show the relevent information. The information being:
 * - The task title
 * - The task description
 * - The task effort
 * - The task assignee
 */

class TaskDelegate: public QAbstractItemDelegate
{
public:
    TaskDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~TaskDelegate();
};

#endif // TASKDELEGATE_H
