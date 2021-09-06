#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QList>
#include <QString>
#include "coin.h"

class Exchange
{
public:
    Exchange(QString name, QString symbol);

    QString name();
    QString symbol();
    QList <Coin> coinList();
    Coin getCoin(QString coin_name);

private:
    QString _name;
    QString _symbol;
    QList <Coin> _coinList;
};

#endif