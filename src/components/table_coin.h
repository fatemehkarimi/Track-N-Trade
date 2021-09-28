#ifndef COIN_TABLE_H
#define COIN_TABLE_H

#include <memory>
#include <QTableView>
#include <QStandardItemModel>
#include <data/coin.h>

class CoinTable : public QTableView
{
    Q_OBJECT
public:
    explicit CoinTable(QString object_name);
    void clear();
    void addCoin(std::shared_ptr <Coin> coin);

signals:
    void coinListUpdated();

private:
    QStandardItemModel* tableModel;
    QMap <QString, std::shared_ptr <Coin> > coinList;
};

#endif