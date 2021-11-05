#include <data/price.h>
#include "delegate_asset_price_change.h"

void AssetPriceChangeDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    double percentage = std::ceil(price.getChangePercentage() * 10000) / 100.0;
    QString changeReper = "";
    if(percentage > 0)
        changeReper = "+";

    changeReper += (QString::number(percentage) + "%");

    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont font = fontSettings.getMarketTablePriceChangeFont();
    painter->setFont(font);
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