#ifndef PAIR_H
#define PAIR_H

#include <QtWidgets>
#include "asset.h"

class Pair {
public:
    Pair(QString id, QString symbol, Asset base, Asset quote);
    QString getSymbol();
    Asset getBase();
    Asset getQuote();
    QString getBaseSymbol();
    QString getQuoteSymbol();

private:
    QString id;
    QString symbol;
    Asset base;
    Asset quote;
};

#endif