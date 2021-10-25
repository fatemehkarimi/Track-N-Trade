#ifndef TABLE_MARKET_H
#define TABLE_MARKET_H

#include <memory>
#include <QTableView>
#include <QStandardItemModel>
#include <data/pair.h>
#include <data/price.h>
#include <data/container.h>

class MarketTable : public QTableView
{
    Q_OBJECT
public:
    explicit MarketTable(QString object_name);
    void clear();
    void addPair(std::shared_ptr <Pair> pair);
    void updatePairPrice(Price price);
    void updatePairPriceChange(Price price);

signals:
    void assetListUpdated();

private:
    QStandardItemModel* tableModel;
    Container <Pair> pairContainer;
};

#endif