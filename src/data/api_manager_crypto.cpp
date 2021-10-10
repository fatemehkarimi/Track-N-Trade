#include <QEventLoop>
#include <QtConcurrent>
#include "api_manager_crypto.h"

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
    getPairList();
}

void CryptoAPIManager::getAssetList() {
    networkManager->fetchJson(routes->getAssets());
}

std::shared_ptr <Asset> CryptoAPIManager::getAsset(QString symbol) {
    if(!assets.empty())
        return assets[symbol];

    QEventLoop loop;
    QObject::connect(this, &CryptoAPIManager::assetListReady, &loop, &QEventLoop::quit);
    loop.exec();
    return assets[symbol];
}

void CryptoAPIManager::getPairList() {
    networkManager->fetchJson(routes->getPairs());
}

std::shared_ptr <Pair> CryptoAPIManager::getPair(QString symbol) {
    if(!pairList.empty())
        return pairList[symbol];

    QEventLoop loop;
    QObject::connect(this, &CryptoAPIManager::pairListReady, &loop, &QEventLoop::quit);
    loop.exec();
    
    return pairList[symbol];
}

void CryptoAPIManager::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeListPath()) {
        this->clearExchangeList();
        QFuture <QList <QMap <QString, QString> > > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json);

        QList <QMap <QString, QString> > result = future.result();
        for(int i = 0; i < result.size(); ++i)
            addExchange(result[i]["id"], result[i]["name"], result[i]["symbol"]);
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
    else if(url == routes->getPairs()) {
        clearPairList();
        QFuture <QList <QMap <QString, QString> > > future = QtConcurrent::run(parser,
            &JsonParser::parsePairsJson, json);
        
        // Filter those pairs than their quote is usd
        QList <QMap <QString, QString> > result = future.result();
        for(int i = 0; i < result.size(); ++i) {

        }
    }
}

void CryptoAPIManager::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}

std::shared_ptr <Exchange> CryptoAPIManager::getExchange(QString exchangeName) {
    return exchangeList[exchangeName];
}

void CryptoAPIManager::addExchange(QString id, QString name, QString symbol) {
    std::shared_ptr <Exchange> exchange(new Exchange(routes, this, parser, id, name, symbol));
    exchangeList[name] = exchange;
}

void CryptoAPIManager::clearAssetList() {
    assets.clear();
}

void CryptoAPIManager::clearPairList() {
    pairList.clear();
}

void CryptoAPIManager::clearExchangeList() {
    exchangeList.clear();
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