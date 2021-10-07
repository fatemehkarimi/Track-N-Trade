#ifndef DELEGATE_COIN_PRICE_CHANGE_H
#define DELEGATE_COIN_PRICE_CHANGE_H

#include <QtWidgets>
#include <data/price.h>

class CoinPriceChangeDelegate : public QItemDelegate
{
public:
    CoinPriceChangeDelegate(QObject* parent)
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