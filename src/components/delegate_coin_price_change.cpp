#include <data/price.h>
#include "delegate_coin_price_change.h"

void CoinPriceChangeDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    double percentage = price.getChangePercentage();
    QString change_reper = "";
    if(percentage > 0)
        change_reper = "+";
    else if(percentage < 0)
        change_reper = "-";
    change_reper += (QString::number(percentage) + "%");

    QFontMetrics font_metrics(painter->font());

    QRect rect = option.rect;
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + font_metrics.height() / 2);

    QColor green = QColor(70, 203, 130);
    QColor red = QColor(217, 61, 74);

    if(percentage > 0)
        painter->setPen(green);
    else
        painter->setPen(red);

    painter->drawText(rect, Qt::AlignLeft, change_reper);
}