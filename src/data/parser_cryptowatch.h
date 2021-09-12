#ifndef PARSER_CRYPTOWATCH_H
#define PARSER_CRYPTOWATCH_H

#include "parser_json.h"

class CryptowatchParser : public JsonParser
{
public:
    explicit CryptowatchParser();
    bool parseExchangeListJson(QJsonObject, Routes* routes,
        QMap <QString, Exchange*>* exchangeList) override;
    bool parseExchangeDetailJson(QJsonObject json) override;
    bool parseExchangeMarketsJson(QJsonObject json) override;
    bool parseAssetsJson(QJsonObject json) override;
};

#endif