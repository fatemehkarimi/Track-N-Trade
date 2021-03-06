#include <memory>
#include <data/pair.h>
#include <components/tables/table_delegates/delegate_pair.h>

void PairDelegate::paint( QPainter *painter, 
    const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    std::shared_ptr <Pair> pair = index.data().value < std::shared_ptr <Pair> >();
    if(pair == nullptr)
        return;

    QString base = pair->getBaseSymbol().toUpper();
    QString quote = pair->getQuoteSymbol().toUpper();

    painter->setFont(fontStyle);
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
