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

private:
    QString basePath = "https://api.cryptowat.ch";
    QString exchangeListPath = "/exchanges";
};

#endif