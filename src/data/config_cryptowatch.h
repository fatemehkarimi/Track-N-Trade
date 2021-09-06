#ifndef CONFIG_CRYPTOWATCH_H
#define CONFIG_CRYPTOWATCH_H

#include <QString>

class CryptowatchConfig {
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

    QString getExchangeMarketsPaht(QString exchange_symbol) {
        return getBasePath() + "/markets/" + exchange_symbol;
    }

private:
    QString basePath = "https://api.cryptowat.ch";
    QString exchangeListPath = "/exchanges";
};

#endif