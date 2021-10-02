#include <QEventLoop>
#include <QtConcurrent>
#include "exchange_composite.h"
#include "exchange_leaf.h"


CompositeExchange::CompositeExchange(Settings::App* appSettings,
        Routes* api_routes, JsonParser* json_parser)
    : appSettings(appSettings) {
    routes = api_routes;
    parser = json_parser;

    priceTracker = new PriceTracker(routes, parser, appSettings->getPriceRefreshRate());
    networkManager = NetworkManager::getInstance();

    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &CompositeExchange::parseJson);
    QObject::connect(priceTracker, &PriceTracker::pricesUpdated,
                    this, &CompositeExchange::handlePriceUpdates);

    getExchangeList();
    getCoinList();
}

QString CompositeExchange::getName() {
    return nullptr;
}

QString CompositeExchange::getSymbol() {
    return nullptr;
}

std::shared_ptr <Coin> CompositeExchange::getCoin(QString symbol) {
    if(!assets.empty())
        return assets[symbol];

    QEventLoop loop;
    QObject::connect(this, &Exchange::coinListReady, &loop, &QEventLoop::quit);
    loop.exec();
    return assets[symbol];
}

void CompositeExchange::getCoinList() {
    networkManager->fetchJson(routes->getAssets());
}

void CompositeExchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeListPath()) {
        this->clearExchangeList();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json, this);

        bool parsed = future.result();
        if(parsed)
            emit exchangeListReady(exchangeList);
    }
    else if(url == routes->getAssets()) {
        this->clearCoinList();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseAssetsJson, json, &assets);
        
        bool parsed = future.result();
        if(parsed) 
            emit coinListReady(assets);
    }
}

std::shared_ptr <Exchange> CompositeExchange::getExchange(QString exchange_name) {
    return exchangeList[exchange_name];
}

void CompositeExchange::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}

void CompositeExchange::addExchange(QString name, QString symbol) {
    std::shared_ptr <Exchange> exchange(new LeafExchange(this, routes, parser, name, symbol));
    exchangeList[name] = exchange;
}

void CompositeExchange::clearExchangeList() {
    exchangeList.clear();
}

void CompositeExchange::clearCoinList() {
    assets.clear();
}

void CompositeExchange::registerPriceObserver(PriceObserver* observer) {
    this->priceObservers.append(observer);
}

void CompositeExchange::handlePriceUpdates(
        QMap <QString, QMap <QString, double> > prices) {
    for(auto observer : priceObservers)
        observer->getPriceUpdates(prices);
}