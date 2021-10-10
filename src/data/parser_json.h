#ifndef PARSER_JSON_H
#define PARSER_JSON_H

#include <QJsonObject>
#include <QMap>
#include "routes.h"
#include "api_manager.h"

class JsonParser
{
public:
    virtual bool parseExchangeListJson(QJsonObject json, APIManager* refAPI) = 0;
    virtual bool parseExchangeDetailJson(QJsonObject) = 0;
    virtual QList <QString> parseExchangeMarketsJson(QJsonObject) = 0;
    virtual bool parseAssetsJson(QJsonObject, QMap <QString, std::shared_ptr <Asset> >*) = 0;
    virtual QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject) = 0;
    virtual QMap <QString, QMap <QString, double> >
        parseAllPriceChanges(QJsonObject) = 0;
};

#endif