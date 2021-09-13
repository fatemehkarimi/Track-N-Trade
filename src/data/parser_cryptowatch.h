#ifndef PARSER_CRYPTOWATCH_H
#define PARSER_CRYPTOWATCH_H

#include "parser_json.h"

class CryptowatchParser : public JsonParser
{
public:
    explicit CryptowatchParser();
    bool parseExchangeListJson(QJsonObject, Exchange* parent) override;
    bool parseExchangeDetailJson(QJsonObject json) override;
    bool parseExchangeMarketsJson(QJsonObject json, QMap <QString, Coin*>*) override;
    bool parseAssetsJson(QJsonObject json,
        QMap <QString, Coin*>* coinList) override;
};

#endif