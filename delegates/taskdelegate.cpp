#include "taskdelegate.h"

TaskDelegate::TaskDelegate(QObject *parent)
{

}

void TaskDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const{
    /**
     * This method uses QPainter to draw the information I pass into it on to each QListWidgetItem, using the painter allows me to
     * customise the styling such as the fomts and colors used.
     */
    QRect r = option.rect;

    //Color: #C4C4C4
    QPen linePen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

    //Color: #005A83
    QPen lineMarkedPen(QColor::fromRgb(0,90,131), 1, Qt::SolidLine);

    //Color: #333
    QPen fontPen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

    //Color: #fff
    QPen fontMarkedPen(Qt::white, 1, Qt::SolidLine);

    if(option.state & QStyle::State_Selected){
        QLinearGradient gradientSelected(r.left(),r.top(),r.left(),r.height()+r.top());
        gradientSelected.setColorAt(0.0, QColor::fromRgb(27,131,139));
        gradientSelected.setColorAt(0.9, QColor::fromRgb(27,131,139));
        gradientSelected.setColorAt(1.0, QColor::fromRgb(27,131,139));
        painter->setBrush(gradientSelected);
          painter->drawRect(r);

        //BORDER
//        painter->setPen(lineMarkedPen);
//        painter->drawLine(r.topLeft(),r.topRight());
//        painter->drawLine(r.topRight(),r.bottomRight());
//        painter->drawLine(r.bottomLeft(),r.bottomRight());
//        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontMarkedPen);

    } else {
        //BACKGROUND
                    //ALTERNATING COLORS
        painter->setBrush( (index.row() % 2) ? QColor(221, 224, 227) : QColor(221, 224, 227) );
        painter->drawRect(r);

        //BORDER
//        painter->setPen(linePen);
//        painter->drawLine(r.topLeft(),r.topRight());
//        painter->drawLine(r.topRight(),r.bottomRight());
//        painter->drawLine(r.bottomLeft(),r.bottomRight());
//        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontPen);
    }

    //GET TITLE, DESCRIPTION AND ICON
    QIcon ic = QIcon(qvariant_cast<QPixmap>(index.data(Qt::DecorationRole)));
    QString title = index.data(Qt::DisplayRole).toString();
    QString description = index.data(Qt::UserRole + 1).toString();
    QString status = index.data(Qt::ToolTipRole).toString();

    int imageSpace = 10;
    if (!ic.isNull()) {
        //ICON
        r = option.rect.adjusted(5, 10, -10, -10);
        ic.paint(painter, r, Qt::AlignVCenter|Qt::AlignLeft);
        imageSpace = 55;
    }

    //TITLE
    r = option.rect.adjusted(imageSpace, 0, -10, -30);
    painter->setFont( QFont( "Gilroy", 16, QFont::Bold ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignTop|Qt::AlignLeft, title, &r);

    //DESCRIPTION
    r = option.rect.adjusted(imageSpace, 30, -10, 0);
    painter->setFont( QFont( "Gilroy", 12, QFont::Medium ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, description, &r);

    //STATUS
    r = option.rect.adjusted(imageSpace, 30, -10, 0);
    painter->setFont( QFont( "Gilroy", 9, QFont::Normal ) );
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom, status, &r);
}

QSize TaskDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
    /**
    * This method sets the size of each QListWidgetItem
    */
    return QSize(200, 150); // very dumb value
}

TaskDelegate::~TaskDelegate()
{

}
