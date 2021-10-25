#include "parser_cryptowatch.h"
#include "exchange.h"

CryptowatchParser::CryptowatchParser(){}

QList <QMap <QString, QString> > CryptowatchParser::parseExchangeListJson(
        QJsonObject json) {
    QJsonArray exchangeArray = json["result"].toArray();
    QList <QMap <QString, QString> > result;

    foreach (const QJsonValue& value, exchangeArray) {
        QJsonObject obj = value.toObject();
        int id = obj["id"].toInt();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        QString route = obj["route"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        QMap <QString, QString> exchangeInfo;
        exchangeInfo["id"] = QString::number(id);
        exchangeInfo["symbol"] = symbol;
        exchangeInfo["name"] = name;

        result.push_back(exchangeInfo);
    }
    return result;
}

QList <QString> CryptowatchParser::parseExchangePairsJson(QJsonObject json) {
    QList <QString> list;

    QJsonArray asset_array = json["result"].toArray();
    foreach(const QJsonValue& value, asset_array) {
        QJsonObject obj = value.toObject();
        QString pair = obj["pair"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        list.append(pair);
    }
    return list;
}

bool CryptowatchParser::parseAssetsJson(QJsonObject json,
        Container <Asset>* assetList) {
    QJsonArray asset_array = json["result"].toArray();
    foreach(const QJsonValue& value, asset_array) {
        QJsonObject obj = value.toObject();

        QString id = QString::number(obj["id"].toInt());
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        bool fiat = obj["fiat"].toBool();

        std::shared_ptr <Asset> asset(new Asset(id, name, symbol, fiat, ""));
        assetList->add(asset);
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
        if(pair.endsWith("usd"))
            prices[market][pair] = price;
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
            QJsonObject pair_array = summaries_array[key].toObject();
            QJsonObject price_array = pair_array["price"].toObject();
            QJsonObject change_array = price_array["change"].toObject();
            double change_percent = change_array["percentage"].toDouble();

            changes[market][pair] = change_percent;
        }
    }
    return changes;
}

QList <QMap <QString, QString> > CryptowatchParser::parsePairsJson(QJsonObject json) {
    QJsonArray pairsArray = json["result"].toArray();
    QList <QMap <QString, QString> > result;

    foreach(const QJsonValue& value, pairsArray) {
        QJsonObject obj = value.toObject();

        QString id = QString::number(obj["id"].toInt());
        QString symbol = obj["symbol"].toString();

        QJsonObject base = obj["base"].toObject();
        QJsonObject quote = obj["quote"].toObject();
        //TODO: use Id instead of symbol.
        // QString baseId = QString::number(base["id"].toInt());
        // QString quoteId = QString::number(quote["id"].toInt());
        QString baseSymbol = base["symbol"].toString();
        QString quoteSymbol = quote["symbol"].toString();

        QMap <QString, QString> pairInfo;
        pairInfo["id"] = id;
        pairInfo["symbol"] = symbol;
        pairInfo["baseSymbol"] = baseSymbol;
        pairInfo["quoteSymbol"] = quoteSymbol;
        
        result.push_back(pairInfo);
    }
    return result;
}