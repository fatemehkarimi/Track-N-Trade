#ifndef PAIR_H
#define PAIR_H

#include <QtWidgets>
#include "asset.h"
#include "api_item.h"

class Pair : public APIItem {
public:
    Pair(QString id, QString symbol, Asset base, Asset quote);
    QString getId() override;
    QString getSymbol() override;
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