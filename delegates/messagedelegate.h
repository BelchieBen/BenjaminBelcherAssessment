#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

/**
 *  This class inherits from QAbstractItemDelegate which provides the interface to display and edit data items from a model, however I dont use a mode, instead I use a built in method for the QListWidget called SetItemDelegate and that handles most of the configuration for me. \n
 *  This class provides the methods to style the messages on the project chat in a QListWidgetItem to show the relevent information. For messages this information is:
 * - The message title
 * - The message content
 * - The user who posted the message
 * - The date the message was posted
 */

class MessageDelegate: public QAbstractItemDelegate
{
public:
    MessageDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual ~MessageDelegate();
};

#endif // MESSAGEDELEGATE_H
