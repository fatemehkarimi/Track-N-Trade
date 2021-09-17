#include "parser_cryptowatch.h"
#include "exchange_leaf.h"

CryptowatchParser::CryptowatchParser(){}

bool CryptowatchParser::parseExchangeListJson(QJsonObject json, Exchange* parent) {
    QJsonArray exchange_array = json["result"].toArray();

    foreach (const QJsonValue& value, exchange_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        QString route = obj["route"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;
        
        parent->addExchange(name, symbol);
    }
    return true;
}

bool CryptowatchParser::parseExchangeDetailJson(QJsonObject json) {

}

QList <QString> CryptowatchParser::parseExchangeMarketsJson(QJsonObject json) {
    QList <QString> list;

    QJsonArray coin_array = json["result"].toArray();
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();
        QString pair = obj["pair"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        if(pair.endsWith("usd")) {
            pair.chop(3);
            list.append(pair);
        }
    }
    return list;
}

bool CryptowatchParser::parseAssetsJson(QJsonObject json,
        QMap <QString, Coin*>* coinList) {
    QJsonArray coin_array = json["result"].toArray();
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        bool fiat = obj["fiat"].toBool();

        Coin* coin = new Coin(name, symbol, fiat, "");
        (*coinList)[symbol] = coin;
    }
    return true;
}

QMap <QString, QMap <QString, double> > 
        CryptowatchParser::parseAllPairPrices(QJsonObject json) {
    QMap <QString, QMap <QString, double> > prices;
    QJsonObject price_array = json["result"].toObject();
    foreach(const QString& key, price_array.keys()) {
        double price = price_array.value(key).toDouble();
        QStringList result = key.split(":");

        if(result.size() < 3)
            continue;
        if(result[0] != "market")
            continue;
        
        QString market = result[1];
        QString pair = result[2];
        if(pair.endsWith(pair)) {
            pair.chop(3);
            prices[market][pair] = price;
        }
    }
    return prices;
}