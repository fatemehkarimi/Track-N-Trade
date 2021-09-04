#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QList>
#include <QString>
#include "coin.h"

class Exchange
{
public:
    Exchange(QString name, QList <Coin> coin_list);

    QString name();
    QList <Coin> coinList();
    Coin getCoin(QString coin_name);

private:
    QString _name;
    QList <Coin> _coinList;
};

#endif