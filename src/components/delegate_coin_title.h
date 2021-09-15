#include <QtWidgets>

class CoinTitleDelegate : public QItemDelegate
{
public:
    CoinTitleDelegate( QObject *parent, QString symbol, QString unit ) 
    : QItemDelegate(parent),
      symbol(symbol),
      unit(unit) {}

    void paint( QPainter *painter, const QStyleOptionViewItem &option, 
        const QModelIndex &index ) const;

    bool editorEvent(QEvent*, QAbstractItemModel*, const QStyleOptionViewItem &,
        const QModelIndex &) {
        return false;
    }

    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &,
        const QModelIndex &) const {
            return Q_NULLPTR;
    }

private:
    QString symbol;
    QString unit;
};
