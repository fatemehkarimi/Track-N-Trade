#ifndef PARSER_JSON_H
#define PARSER_JSON_H

#include <memory>
#include <QJsonObject>
#include <QMap>
#include "routes.h"
#include "asset.h"
#include "container.h"
#include "ohlc.h"


class JsonParser
{
public:
    virtual QList <QMap <QString, QString> > parseExchangeListJson(QJsonObject json) = 0;
    virtual QList <QString> parseExchangePairsJson(QJsonObject) = 0;
    virtual QList <QMap <QString, QString> > parsePairsJson(QJsonObject json) = 0;

    //TODO: assets json should return list.
    virtual bool parseAssetsJson(QJsonObject, Container <Asset>*) = 0;

    virtual QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject) = 0;

    virtual QMap <QString, QMap <QString, double> > 
        parseAllPriceChanges(QJsonObject) = 0;

    virtual double parsePairPrice(QJsonObject) = 0; 
    virtual double parsePairPriceChange(QJsonObject) = 0;
    virtual double parsePairLowestPrice(QJsonObject) = 0;
    virtual double parsePairHighestPrice(QJsonObject) = 0;
    virtual QMap <QString, double> parsePairSummary(QJsonObject) = 0;
    virtual QList <OHLC> parseOHLC(QJsonObject) = 0;
};

#endif