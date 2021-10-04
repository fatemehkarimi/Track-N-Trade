#include <data/price.h>
#include "delegate_coin_price.h"

void CoinPriceDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    QString latestP = "";
    if(price.getLatestPrice() >= 0)
        latestP = QString::number(price.getLatestPrice());

    QFontMetrics font_metrics(painter->font());

    QRect rect = option.rect;
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + font_metrics.height() / 2);

    QColor green = QColor(70, 203, 130);
    QColor red = QColor(217, 61, 74);
    QColor gray = QColor(62, 64, 69);

    if(price.getPriceStatus() == Price::INCREASE)
        painter->setPen(green);
    else if(price.getPriceStatus() == Price::NOCHANGE)
        painter->setPen(gray);
    else
        painter->setPen(red);

    painter->drawText(rect, Qt::AlignLeft, latestP);
}