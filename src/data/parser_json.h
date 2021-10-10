#ifndef PARSER_JSON_H
#define PARSER_JSON_H

#include <memory>
#include <QJsonObject>
#include <QMap>
#include "routes.h"
#include "asset.h"

class JsonParser
{
public:
    virtual QList <QMap <QString, QString> > parseExchangeListJson(
        QJsonObject json) = 0;
    virtual QList <QString> parseExchangePairsJson(QJsonObject) = 0;

    virtual bool parseAssetsJson(QJsonObject,
        QMap <QString, std::shared_ptr <Asset> >*) = 0;
    virtual QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject) = 0;
    virtual QMap <QString, QMap <QString, double> >
        parseAllPriceChanges(QJsonObject) = 0;
};

#endif