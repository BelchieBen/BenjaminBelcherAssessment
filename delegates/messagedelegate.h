#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

class MessageDelegate: public QAbstractItemDelegate
{
public:
    MessageDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual ~MessageDelegate();
};

#endif // MESSAGEDELEGATE_H
