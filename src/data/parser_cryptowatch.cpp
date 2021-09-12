#include "parser_cryptowatch.h"
#include "exchange_leaf.h"

CryptowatchParser::CryptowatchParser(){}

bool CryptowatchParser::parseExchangeListJson(QJsonObject json, Routes* routes,
    QMap <QString, Exchange*>* exchangeList) {
    QJsonArray exchange_array = json["result"].toArray();

    foreach (const QJsonValue& value, exchange_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        QString route = obj["route"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        LeafExchange* exchange = new LeafExchange(routes, name, symbol);
        (*exchangeList)[name] = exchange;
    }
    return true;
}

bool CryptowatchParser::parseExchangeDetailJson(QJsonObject json) {

}

bool CryptowatchParser::parseExchangeMarketsJson(QJsonObject json) {

}

bool CryptowatchParser::parseAssetsJson(QJsonObject json,
    QMap <QString, Coin*>* coinList) {
    QJsonArray coin_array = json["result"].toArray();
    QJsonDocument doc(json);
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        bool fiat = obj["fiat"].toBool();

        Coin* coin = new Coin(name, symbol, fiat, "");
        (*coinList)[name] = coin;
    }
    return true;
}