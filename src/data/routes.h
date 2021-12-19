#ifndef ROUTES_H
#define ROUTES_H

#include <QtGlobal>
#include <QString>

class Routes {
public:
    virtual QString getBasePath() = 0;
    virtual QString getExchangeListPath() = 0;
    virtual QString getExchangeDetailPath(QString exchangeSymbol) = 0;
    virtual QString getExchangePairsPath(QString exchangeSymbol) = 0;
    virtual QString getAssets() = 0;
    virtual QString getAllPrices() = 0;
    virtual QString getAllPriceChanges() = 0;
    virtual QString getPairs() = 0;
    virtual QString getPairPrice(QString exchangeSymbol, QString pair) = 0;
    virtual QString getPairPriceChange(QString exchangeSymbol, QString pair) = 0;
    virtual QString getPairHighestPrice(QString exchangeSymbol, QString pair) = 0;
    virtual QString getPairLowestPrice(QString exchangeSymbol, QString pair) = 0;
    virtual QString getOHLCPath(
        QString exchangeSymbol, QString pair, int period, qint64 after) = 0;

    virtual QString getOHLCPath(
        QString exchangeSymbol, QString pair,
        int period, qint64 before, qint64 after) = 0;
};
#endif