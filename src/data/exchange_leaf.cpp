#include "exchange_leaf.h"

LeafExchange::LeafExchange(Routes* api_routes, 
    QString exchange_name, QString exchange_symbol)
    : name(exchange_name),
    symbol(exchange_symbol),
    routes(api_routes) {
    networkManager = new NetworkManager();
}

QString LeafExchange::getName() {
    return name;
}

QString LeafExchange::getSymbol() {
    return symbol;
}

void LeafExchange::getCoin(QString coin_symbol) {
    
}

void LeafExchange::getCoinList() {
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &LeafExchange::getCoinListJson);
    networkManager->fetchJson(routes->getExchangeMarketsPath(symbol));
}

void LeafExchange::getCoinListJson(QJsonObject json) {
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &LeafExchange::getCoinListJson);
    
    QJsonArray coin_array = json["result"].toArray();
    foreach(const QJsonValue& value, coin_array) {
        QJsonObject obj = value.toObject();
        QString pair = obj["pair"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;
    }
}

void LeafExchange::getDefaultExchange() {

}

void LeafExchange::setDefaultExchange(QString exchange_symbol) {

}

void LeafExchange::getExchange(QString exchange_symbol) {

}

void LeafExchange::getExchangeList() {

}