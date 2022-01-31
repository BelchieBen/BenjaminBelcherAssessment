#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>


class TaskDelegate: public QAbstractItemDelegate
{
public:
    TaskDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~TaskDelegate();
};

#endif // TASKDELEGATE_H
