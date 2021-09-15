#include <QtWidgets>

class MyDelegate : public QItemDelegate
{
public:
    MyDelegate( QObject *parent, QString symbol, QString unit ) 
    : QItemDelegate(parent),
      symbol(symbol),
      unit(unit) {}

    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    bool editorEvent(QEvent*, QAbstractItemModel*, const QStyleOptionViewItem &, const QModelIndex &)
    { return false; }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    { return Q_NULLPTR; }

private:
    QString symbol;
    QString unit;
};

void MyDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QItemDelegate::paint(painter, option, index);
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
