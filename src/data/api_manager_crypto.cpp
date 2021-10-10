#include <QEventLoop>
#include <QtConcurrent>
#include "api_manager_crypto.h"
#include "exchange_leaf.h"


CryptoAPIManager::CryptoAPIManager(Settings::App* appSettings,
        Routes* api_routes, JsonParser* json_parser)
    : appSettings(appSettings) {
    routes = api_routes;
    parser = json_parser;

    priceTracker = new PriceTracker(routes, parser, appSettings->getPriceRefreshRate());
    networkManager = NetworkManager::getInstance();

    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &CryptoAPIManager::parseJson);
    QObject::connect(priceTracker, &PriceTracker::pricesUpdated,
                    this, &CryptoAPIManager::handlePriceUpdates);
    QObject::connect(priceTracker, &PriceTracker::priceChangesUpdated,
                    this, &CryptoAPIManager::handlePriceChangesUpdates);

    getExchangeList();
    getAssetList();
}

std::shared_ptr <Asset> CryptoAPIManager::getAsset(QString symbol) {
    if(!assets.empty())
        return assets[symbol];

    QEventLoop loop;
    QObject::connect(this, &CryptoAPIManager::assetListReady, &loop, &QEventLoop::quit);
    loop.exec();
    return assets[symbol];
}

void CryptoAPIManager::getAssetList() {
    networkManager->fetchJson(routes->getAssets());
}

void CryptoAPIManager::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeListPath()) {
        this->clearExchangeList();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json, this);

        bool parsed = future.result();
        if(parsed)
            emit exchangeListReady(exchangeList);
    }
    else if(url == routes->getAssets()) {
        this->clearAssetList();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseAssetsJson, json, &assets);
        
        bool parsed = future.result();
        if(parsed) 
            emit assetListReady(assets);
    }
}

std::shared_ptr <Exchange> CryptoAPIManager::getExchange(QString exchangeName) {
    return exchangeList[exchangeName];
}

void CryptoAPIManager::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}

void CryptoAPIManager::addExchange(QString name, QString symbol) {
    std::shared_ptr <Exchange> exchange(new LeafExchange(this, routes, parser, name, symbol));
    exchangeList[name] = exchange;
}

void CryptoAPIManager::clearExchangeList() {
    exchangeList.clear();
}

void CryptoAPIManager::clearAssetList() {
    assets.clear();
}

void CryptoAPIManager::registerPriceObserver(PriceObserver* observer) {
    this->priceObservers.append(observer);
}

void CryptoAPIManager::handlePriceUpdates(
        QMap <QString, QMap <QString, Price> > prices) {
    for(auto observer : priceObservers)
        observer->getPriceUpdates(prices);
}

void CryptoAPIManager::handlePriceChangesUpdates(
        QMap <QString, QMap <QString, Price> > prices) {
    for(auto observer : priceObservers)
        observer->getPriceChangesUpdates(prices);
}