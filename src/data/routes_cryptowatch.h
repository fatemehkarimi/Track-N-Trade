#ifndef ROUTES_CRYPTOWATCH_H
#define ROUTES_CRYPTOWATCH_H

#include <QString>
#include "routes.h"

class CryptowatchRoutes : public Routes
{
public:
    QString getBasePath() {
        return basePath;
    }

    QString getExchangeListPath() {
        return basePath + exchangeListPath;
    }

    QString getExchangeDetailPath(QString exchange_symbol) {
        return getExchangeListPath() + "/" + exchange_symbol;
    }

    QString getExchangeMarketsPath(QString exchange_symbol) {
        return getBasePath() + marketsPath + "/" + exchange_symbol;
    }

    QString getAssets() {
        return getBasePath() + assetsPath;
    }

    QString getPairPrice(QString exchange_symbol, QString pair) {
        return getExchangeMarketsPath(exchange_symbol) + "/" + pair + pricePath;
    }

    QString getAllPrices() {
        return getBasePath() + marketsPath + allPricesPath;
    }

private:
    QString basePath = "https://api.cryptowat.ch";
    QString exchangeListPath = "/exchanges";
    QString marketsPath = "/markets";
    QString assetsPath = "/assets";
    QString pricePath = "/price";
    QString allPricesPath = "/prices";
};

#endif
