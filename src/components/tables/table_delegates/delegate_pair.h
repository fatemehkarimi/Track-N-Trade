#ifndef DELEGATE_PAIR_H
#define DELEGATE_PAIR_H

#include <QtWidgets>
#include <settings/settings_app.h>
#include <settings/settings_font.h>

class PairDelegate : public QItemDelegate
{
public:
    PairDelegate( QObject* parent, QFont fontStyle)
    : QItemDelegate(parent),
    fontStyle(fontStyle)
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

private:
    QFont fontStyle;
};

#endif
