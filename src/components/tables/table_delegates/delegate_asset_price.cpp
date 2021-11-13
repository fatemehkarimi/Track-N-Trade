#include <data/price.h>
#include <components/tables/table_delegates/delegate_asset_price.h>

void AssetPriceDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Price price = index.data().value <Price>();
    QString latestP = "";
    if(price.getLatestPrice() > 0)
        latestP = QString::number(price.getLatestPrice());

    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont font = fontSettings.getMarketTablePriceFont();
    painter->setFont(font);
    
    QFontMetrics fontMetrics(painter->font());
    QRect boundingRect = fontMetrics.boundingRect(latestP);
    QRect rect = option.rect;
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + (rect.height() - boundingRect.height()) / 2);

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