#ifndef PAIR_H
#define PAIR_H

#include <QtWidgets>
#include "coin.h"

class Pair {
public:
    Pair(QString symbol, Coin base, Coin quote);
    QString getSymbol();
    Coin getBaseCoin();
    Coin getQuoteCoin();
    QString getBaseSymbol();
    QString getQuoteSymbol();

private:
    QString symbol;
    Coin base;
    Coin quote;
};

#endif