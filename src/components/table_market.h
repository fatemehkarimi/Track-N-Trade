#ifndef TABLE_MARKET_H
#define TABLE_MARKET_H

#include <memory>
#include <QTableView>
#include <QStandardItemModel>
#include <data/asset.h>
#include <data/price.h>

class MarketTable : public QTableView
{
    Q_OBJECT
public:
    explicit MarketTable(QString object_name);
    void clear();
    void addAsset(std::shared_ptr <Asset> asset);
    void updateAssetPrice(QString symbol, Price price);
    void updatePriceChange(QString symbol, Price price);

signals:
    void assetListUpdated();

private:
    QStandardItemModel* tableModel;
    // Key is asset symbol
    QMap <QString, std::shared_ptr <Asset> > assetList;
};

#endif