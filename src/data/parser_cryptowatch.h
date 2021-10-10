#ifndef PARSER_CRYPTOWATCH_H
#define PARSER_CRYPTOWATCH_H

#include "api_manager.h"
#include "parser_json.h"

class CryptowatchParser : public JsonParser
{
public:
    explicit CryptowatchParser();
    bool parseExchangeListJson(QJsonObject json, APIManager* refAPI) override;
    bool parseExchangeDetailJson(QJsonObject json) override;
    QList <QString> parseExchangeMarketsJson(QJsonObject json) override;
    bool parseAssetsJson(QJsonObject json,
        QMap <QString, std::shared_ptr <Asset> >* assetList) override;
    QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject json) override;
    QMap <QString, QMap <QString, double> >
        parseAllPriceChanges(QJsonObject json) override;
};

#endif