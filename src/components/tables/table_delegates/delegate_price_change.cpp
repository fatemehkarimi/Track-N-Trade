#include <data/price.h>
#include <components/tables/table_delegates/delegate_price_change.h>

void PriceChangeDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    double percentage = std::ceil(price.getChangePercentage() * 10000) / 100.0;
    QString changeReper = "";
    if(percentage > 0)
        changeReper = "+";
    changeReper += (QString::number(percentage) + "%");

    painter->setFont(fontStyle);
    QFontMetrics fontMetrics(painter->font());
    QRect boundingRect = fontMetrics.boundingRect(changeReper);

    QRect rect = option.rect;
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + (rect.height() - boundingRect.height()) / 2);

    QColor green = QColor(70, 203, 130);
    QColor red = QColor(217, 61, 74);

    if(percentage > 0)
        painter->setPen(green);
    else
        painter->setPen(red);

    painter->drawText(rect, Qt::AlignLeft, changeReper);
}