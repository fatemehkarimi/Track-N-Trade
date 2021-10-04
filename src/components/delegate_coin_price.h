#ifndef DELEGATE_COIN_PRICE_H
#define DELECATE_COIN_PRICE_H

#include <QtWidgets>
#include <data/price.h>

class CoinPriceDelegate : public QItemDelegate
{
public:
    CoinPriceDelegate(QObject* parent)
    : QItemDelegate(parent)
    {}

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
};

#endif