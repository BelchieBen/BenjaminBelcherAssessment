#ifndef COMMENTDELEGATE_H
#define COMMENTDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

class CommentDelegate: public QAbstractItemDelegate
{
public:
    CommentDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~CommentDelegate();
};

#endif // COMMENTDELEGATE_H
