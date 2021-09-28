#include "delegate_coin_title.h"

void CoinTitleDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QMap <QString, QString> data = index.data().value < QMap <QString, QString> >();
    QString symbol = data["symbol"].toUpper();
    QString unit = data["unit"];

    QFontMetrics font_metrics(painter->font());

    QRect rect = option.rect;
    rect.setX(5);
    rect.setY(rect.y() + font_metrics.height() / 2);

    painter->setPen(Qt::black);
    painter->drawText(rect, Qt::AlignLeft, symbol);

    QColor gray = QColor(103, 106, 110);
    painter->setPen(gray);
    rect.setX(rect.x() + font_metrics.width(symbol));
    painter->drawText(rect, Qt::AlignLeft, "/" + unit);
}
