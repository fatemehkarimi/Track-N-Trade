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
        exchangeList.clear();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json, routes, &exchangeList);

        bool parsed = future.result();
        if(parsed)
            emit exchangeListReady(exchangeList);
    }
}

void CompositeExchange::getExchange(QString exchange_name) {
}

void CompositeExchange::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}
