#ifndef COMMENTDELEGATE_H
#define COMMENTDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

/**
 * This class inherits from QAbstractItemDelegate which provides the interface to display and edit data items from a model, however I dont use a mode, instead I use a built in method for the QListWidget called SetItemDelegate and that handles most of the configuration for me. \n
 * This class provides the methods to style the comments in a QListWidgetItem to show the relevent information. This information being:
 * - The comment text
 * - The user who posted the comment
 * - The date that the comment was poste
 */

class CommentDelegate: public QAbstractItemDelegate
{
public:
    CommentDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~CommentDelegate();
};

#endif // COMMENTDELEGATE_H
