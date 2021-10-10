#ifndef ROUTES_H
#define ROUTES_H

#include <QString>

class Routes {
public:
    virtual QString getBasePath() = 0;
    virtual QString getExchangeListPath() = 0;
    virtual QString getExchangeDetailPath(QString exchange_symbol) = 0;
    virtual QString getExchangePairsPath(QString exchange_symbol) = 0;
    virtual QString getAssets() = 0;
    virtual QString getPairPrice(QString exchange_symbol, QString pair) = 0;
    virtual QString getAllPrices() = 0;
    virtual QString getAll24hSummeries() = 0;
    virtual QString getPairs() = 0;
};
#endif