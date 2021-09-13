#include <QtConcurrent>
#include "exchange_composite.h"
#include "exchange_leaf.h"


CompositeExchange::CompositeExchange(Routes* api_routes, JsonParser* json_parser) {
    routes = api_routes;
    parser = json_parser;
    networkManager = new NetworkManager();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &CompositeExchange::parseJson);
    getExchangeList();
    getCoinList();
}

QString CompositeExchange::getName() {
    return nullptr;
}

QString CompositeExchange::getSymbol() {
    return nullptr;
}

void CompositeExchange::getCoin(QString symbol) {
}

void CompositeExchange::getCoinList() {
    networkManager->fetchJson(routes->getAssets());
}

void CompositeExchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeListPath()) {
        // TODO objects must be deleted
        exchangeList.clear();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json, routes, &exchangeList);

        bool parsed = future.result();
        if(parsed)
            emit exchangeListReady(exchangeList);
    }
    else if(url == routes->getAssets()) {
        assets.clear();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseAssetsJson, json, &assets);
        
        bool parsed = future.result();
        if(parsed) 
            emit coinListReady(assets);
    }
}

Exchange* CompositeExchange::getExchange(QString exchange_name) {
    return exchangeList[exchange_name];
}

void CompositeExchange::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}
