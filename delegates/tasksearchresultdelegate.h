#ifndef TASKSEARCHRESULTDELEGATE_H
#define TASKSEARCHRESULTDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

class TaskSearchResultDelegate: public QAbstractItemDelegate
{
public:
    TaskSearchResultDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~TaskSearchResultDelegate();
};

#endif // TASKSEARCHRESULTDELEGATE_H
