#ifndef PARSER_JSON_H
#define PARSER_JSON_H

#include <QJsonObject>
#include <QMap>
#include "exchange.h"
#include "routes.h"

class JsonParser
{
public:
    virtual bool parseExchangeListJson(QJsonObject json, Exchange* parent) = 0;
    virtual bool parseExchangeDetailJson(QJsonObject) = 0;
    virtual QList <QString> parseExchangeMarketsJson(QJsonObject) = 0;
    virtual bool parseAssetsJson(QJsonObject, QMap <QString, std::shared_ptr <Coin> >*) = 0;
    virtual QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject) = 0;
};

#endif