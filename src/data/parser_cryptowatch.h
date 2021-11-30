#ifndef PARSER_CRYPTOWATCH_H
#define PARSER_CRYPTOWATCH_H

#include "parser_json.h"

class CryptowatchParser : public JsonParser
{
public:
    explicit CryptowatchParser();
    QList <QMap <QString, QString> > parseExchangeListJson(
        QJsonObject json) override;
    QList <QMap <QString, QString> > parsePairsJson(QJsonObject json) override;
    QList <QString> parseExchangePairsJson(QJsonObject json) override;

    bool parseAssetsJson(QJsonObject json,
        Container <Asset> * assetList) override;
    QMap <QString, QMap <QString, double> > 
        parseAllPairPrices(QJsonObject json) override;
    QMap <QString, QMap <QString, double> >
        parseAllPriceChanges(QJsonObject json) override;

    double parsePairPrice(QJsonObject json) override;
    double parsePairPriceChange(QJsonObject) override;
    QMap <QString, double> parsePairSummary(QJsonObject) override;
};

#endif