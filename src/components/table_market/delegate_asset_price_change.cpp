#include <data/price.h>
#include "delegate_asset_price_change.h"

void AssetPriceChangeDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    double percentage = std::ceil(price.getChangePercentage() * 10000) / 100.0;
    QString change_reper = "";
    if(percentage > 0)
        change_reper = "+";

    change_reper += (QString::number(percentage) + "%");

    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont font = fontSettings.getMarketTablePriceChangeFont();
    painter->setFont(font);
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