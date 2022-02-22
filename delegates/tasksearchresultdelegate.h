#ifndef TASKSEARCHRESULTDELEGATE_H
#define TASKSEARCHRESULTDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

/**
 * This class inherits from QAbstractItemDelegate which provides the interface to display and edit data items from a model, however I dont use a mode, instead I use a built in method for the QListWidget called SetItemDelegate and that handles most of the configuration for me. \n
 * This class provides the methods to style the resulted tasks after the user has preformed a search, these are displayed in a QListWidgetItem and shows the relevent information about each task. This being:
 * - The task title
 * - The task description
 * - The task effort
 * - The task assignee
 */

class TaskSearchResultDelegate: public QAbstractItemDelegate
{
public:
    TaskSearchResultDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~TaskSearchResultDelegate();
};

#endif // TASKSEARCHRESULTDELEGATE_H
