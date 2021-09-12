#ifndef PARSER_JSON_H
#define PARSER_JSON_H

#include <QJsonObject>
#include <QMap>
#include "exchange.h"
#include "routes.h"

class JsonParser
{
public:
    virtual bool parseExchangeListJson(QJsonObject json, Routes* routes, 
        QMap <QString, Exchange*>*) = 0;
    virtual bool parseExchangeDetailJson(QJsonObject) = 0;
    virtual bool parseExchangeMarketsJson(QJsonObject, QMap <QString, Coin*>*) = 0;
    virtual bool parseAssetsJson(QJsonObject, QMap <QString, Coin*>*) = 0;
};


#endif