#ifndef COIN_TABLE_H
#define COIN_TABLE_H

#include <QTableWidget>
#include <data/coin.h>

class CoinTable : public QTableWidget
{
public:
    explicit CoinTable(QString object_name);
    void clear();
    void addCoin(Coin* coin);

private:
    QMap <QString, Coin*> coinList;
};

#endif