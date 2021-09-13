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

bool CryptowatchParser::parseExchangeMarketsJson(QJsonObject json, 
    QMap <QString, Coin*>* coinList) {
    QJsonArray coin_array = json["result"].toArray();
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();
        QString pair = obj["pair"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        if(pair.endsWith("usd")) {
            //TODO: ask the root class for pointer to coin;
        }
    }
    return true;
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