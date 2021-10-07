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
        QMap <QString, std::shared_ptr <Asset> >* coinList) {
    QJsonArray coin_array = json["result"].toArray();
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();

        int id = obj["id"].toInt();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        bool fiat = obj["fiat"].toBool();

        std::shared_ptr <Asset> asset(new Asset(id, name, symbol, fiat, ""));
        (*coinList)[symbol] = asset;
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
        if(pair.endsWith("usd")) {
            pair.chop(3);
            prices[market][pair] = price;
        }
    }
    return prices;
}

QMap <QString, QMap <QString, double> >
        CryptowatchParser::parseAllPriceChanges(QJsonObject json) {
    QMap <QString, QMap <QString, double> > changes;
    QJsonObject summaries_array = json["result"].toObject();
    foreach(const QString& key, summaries_array.keys()) {
        QStringList result = key.split(":");

        if(result.size() < 2)
            continue;
        
        QString market = result[0];
        QString pair = result[1];
        if(pair.endsWith("usd")) {
            pair.chop(3);

            QJsonObject pair_array = summaries_array[key].toObject();
            QJsonObject price_array = pair_array["price"].toObject();
            QJsonObject change_array = price_array["change"].toObject();
            double change_percent = change_array["percentage"].toDouble();

            changes[market][pair] = change_percent;
        }
    }
    return changes;
}