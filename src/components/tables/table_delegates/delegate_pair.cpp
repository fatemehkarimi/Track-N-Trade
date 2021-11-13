#include <components/tables/table_delegates/delegate_pair.h>

void PairDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QMap <QString, QString> data = index.data().value < QMap <QString, QString> >();
    QString base = data["base"].toUpper();
    QString quote = data["quote"].toUpper();

    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont font = fontSettings.getMarketTablePairFont();
    painter->setFont(font);
    QFontMetrics fontMetrics(painter->font());
    QRect boundingRect = fontMetrics.boundingRect(base + "/" + quote);

    QRect rect = option.rect;
    rect.setX(5);
    rect.setY(rect.y() + (rect.height() - boundingRect.height()) / 2);

    painter->setPen(Qt::black);
    painter->drawText(rect, Qt::AlignLeft, base);

    QColor gray = QColor(103, 106, 110);
    painter->setPen(gray);
    rect.setX(rect.x() + fontMetrics.width(base));
    painter->drawText(rect, Qt::AlignLeft, "/" + quote);
}
