#include <QtConcurrent>
#include "exchange_leaf.h"

LeafExchange::LeafExchange(Exchange* parent,Routes* api_routes,
        JsonParser* json_parser, QString exchange_name, QString exchange_symbol)
    : parent(parent),
    name(exchange_name),
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
        QFuture < QList <QString> > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeMarketsJson, json);
        
        QList <QString> symbolList = future.result();
        for(int i = 0; i < symbolList.size(); ++i) {
            Coin* coin = parent->getCoin(symbolList[i]);
            if(coin != nullptr)
                coinList[coin->symbol()] = coin;
        }
        emit coinListReady(coinList);
    }
}

QString LeafExchange::getName() {
    return name;
}

QString LeafExchange::getSymbol() {
    return symbol;
}

Coin* LeafExchange::getCoin(QString coin_symbol) {
    return coinList[coin_symbol];
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