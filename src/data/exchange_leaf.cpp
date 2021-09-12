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
}

void LeafExchange::getCoinListJson(QJsonObject json) {
}

void LeafExchange::getExchange(QString exchange_name) {
}

void LeafExchange::getExchangeList() {
}