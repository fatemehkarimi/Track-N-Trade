#ifndef ROUTES_CRYPTOWATCH_H
#define ROUTES_CRYPTOWATCH_H

#include <QString>
#include "routes.h"

class CryptowatchRoutes : public Routes
{
public:
    QString getBasePath() override {
        return basePath;
    }

    QString getExchangeListPath() override {
        return basePath + exchangeListPath;
    }

    QString getExchangeDetailPath(QString exchange_symbol) override {
        return getExchangeListPath() + "/" + exchange_symbol;
    }

    QString getExchangePairsPath(QString exchange_symbol) override {
        return getBasePath() + marketsPath + "/" + exchange_symbol;
    }

    QString getAssets() override {
        return getBasePath() + assetsPath;
    }

    QString getPairPrice(QString exchange_symbol, QString pair) override {
        return getExchangePairsPath(exchange_symbol) + "/" + pair + pricePath;
    }

    QString getAllPrices() override {
        return getBasePath() + marketsPath + allPricesPath;
    }

    QString getAllPriceChanges() override {
        return getBasePath() + marketsPath + summariesPath;
    }

    QString getPairs() override {
        return getBasePath() + pairsPath;
    }

private:
    QString basePath = "https://api.cryptowat.ch";
    QString exchangeListPath = "/exchanges";
    QString marketsPath = "/markets";
    QString assetsPath = "/assets";
    QString pricePath = "/price";
    QString allPricesPath = "/prices";
    QString summariesPath = "/summaries";
    QString pairsPath = "/pairs";
};

#endif
