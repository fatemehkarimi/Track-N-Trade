#include <QtConcurrent>
#include "exchange_leaf.h"

LeafExchange::LeafExchange(Routes* api_routes, JsonParser* json_parser,
    QString exchange_name, QString exchange_symbol)
    : name(exchange_name),
    symbol(exchange_symbol),
    routes(api_routes),
    parser(json_parser) {
    networkManager = new NetworkManager();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &LeafExchange::parseJson);
}

void LeafExchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeMarketsPath(symbol)){
        //TODO: perform object deletion
        coinList.clear();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeMarketsJson, json, &coinList);
        
        bool parsed = future.result();
        if(parsed)
            emit coinListReady(coinList);
    }
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
    networkManager->fetchJson(routes->getExchangeMarketsPath(symbol));
}

Exchange* LeafExchange::getExchange(QString exchange_name) {
    return nullptr;
}

void LeafExchange::getExchangeList() {
}

void LeafExchange::addExchange(QString name, QString symbol){
    
}