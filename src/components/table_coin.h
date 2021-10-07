#ifndef COIN_TABLE_H
#define COIN_TABLE_H

#include <memory>
#include <QTableView>
#include <QStandardItemModel>
#include <data/asset.h>
#include <data/price.h>

class CoinTable : public QTableView
{
    Q_OBJECT
public:
    explicit CoinTable(QString object_name);
    void clear();
    void addCoin(std::shared_ptr <Asset> coin);
    void updateCoinPrice(QString symbol, Price price);
    void updatePriceChange(QString symbol, Price price);

signals:
    void coinListUpdated();

private:
    QStandardItemModel* tableModel;
    // Key is coin symbol
    QMap <QString, std::shared_ptr <Asset> > coinList;
};

#endif