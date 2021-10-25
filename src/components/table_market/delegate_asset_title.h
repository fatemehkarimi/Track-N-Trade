#ifndef DELEGATE_ASSET_TITLE_H
#define DELEGATE_ASSET_TITLE_H

#include <QtWidgets>

class AssetTitleDelegate : public QItemDelegate
{
public:
    AssetTitleDelegate( QObject* parent)
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
