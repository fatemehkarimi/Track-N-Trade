#ifndef DELEGATE_PRICE_H
#define DELEGATE_PRICE_H

#include <QtWidgets>
#include <settings/settings_app.h>
#include <settings/settings_font.h>
#include <data/price.h>

class PriceDelegate : public QItemDelegate
{
public:
    PriceDelegate(QObject* parent)
    : QItemDelegate(parent) {}

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