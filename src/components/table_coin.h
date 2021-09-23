#ifndef COIN_TABLE_H
#define COIN_TABLE_H

#include <memory>
#include <QTableWidget>
#include <data/coin.h>

class CoinTable : public QTableWidget
{
public:
    explicit CoinTable(QString object_name);
    void clear();
    void addCoin(std::shared_ptr <Coin> coin);

private:
    QMap <QString, std::shared_ptr <Coin> > coinList;
};

#endif