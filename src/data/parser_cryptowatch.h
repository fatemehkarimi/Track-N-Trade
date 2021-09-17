#ifndef PARSER_CRYPTOWATCH_H
#define PARSER_CRYPTOWATCH_H

#include "parser_json.h"

class CryptowatchParser : public JsonParser
{
public:
    explicit CryptowatchParser();
    bool parseExchangeListJson(QJsonObject, Exchange* parent) override;
    bool parseExchangeDetailJson(QJsonObject json) override;
    QList <QString> parseExchangeMarketsJson(QJsonObject json) override;
    bool parseAssetsJson(QJsonObject json,
        QMap <QString, Coin*>* coinList) override;
    QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject json) override;
};

#endif