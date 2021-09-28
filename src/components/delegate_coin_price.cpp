#include "delegate_coin_price.h"

void CoinPriceDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QMap <QString, QString> data = index.data().value < QMap <QString, QString> >();
    QString price = data["price"];

    QFontMetrics font_metrics(painter->font());

    QRect rect = option.rect;
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + font_metrics.height() / 2);

    QColor green = QColor(59, 112, 52);
    painter->setPen(green);
    painter->drawText(rect, Qt::AlignLeft, price);
}