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

    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(this, &CryptoAPIManager::assetListReady,
            this, [=](){
                getPairList();
            });

    getExchangeList();
    getAssetList();
}

void CryptoAPIManager::getAssetList() {
    networkManager->fetchJson(routes->getAssets());
}

std::shared_ptr <Asset> CryptoAPIManager::getAsset(QString symbol) {
    if(!assetContainer.empty())
        return assetContainer.getBySymbol(symbol);

    QEventLoop loop;
    QObject::connect(this, &CryptoAPIManager::assetListReady, &loop, &QEventLoop::quit);
    loop.exec();
    return assetContainer.getBySymbol(symbol);
}

void CryptoAPIManager::getPairList() {
    networkManager->fetchJson(routes->getPairs());
}

std::shared_ptr <Pair> CryptoAPIManager::getPairBySymbol(QString symbol) {
    if(!pairContainer.empty())
        return pairContainer.getBySymbol(symbol);

    QEventLoop loop;
    QObject::connect(this, &CryptoAPIManager::pairListReady, &loop, &QEventLoop::quit);
    loop.exec();
    
    return pairContainer.getBySymbol(symbol);
}

void CryptoAPIManager::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeListPath()) {
        exchangeContainer.clearAll();
        QFuture <QList <QMap <QString, QString> > > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeListJson, json);

        QList <QMap <QString, QString> > result = future.result();
        for(int i = 0; i < result.size(); ++i)
            addExchange(result[i]["id"], result[i]["name"], result[i]["symbol"]);
        emit exchangeListReady(exchangeContainer);
    }
    else if(url == routes->getAssets()) {
        assetContainer.clearAll();
        QFuture <bool> future = QtConcurrent::run(parser,
            &JsonParser::parseAssetsJson, json, &assetContainer);
        
        bool parsed = future.result();
        if(parsed)
            emit assetListReady(assetContainer);
    }
    else if(url == routes->getPairs()) {
        pairContainer.clearAll();
        QFuture <QList <QMap <QString, QString> > > future = QtConcurrent::run(parser,
            &JsonParser::parsePairsJson, json);
        
        // TODO Filter those pairs than their quote is usd
        QList <QMap <QString, QString> > result = future.result();
        for(int i = 0; i < result.size(); ++i) {
            QMap <QString, QString> pairInfo = result[i];
            std::shared_ptr <Asset> base = getAsset(pairInfo["baseSymbol"]);
            std::shared_ptr <Asset> quote = getAsset(pairInfo["quoteSymbol"]);

            // if base or quote not found for a pair then ignore it.
            if(base == nullptr || quote == nullptr)
                continue;

            // TODO: do not use constants
            if(quote->getSymbol() != "usd")
                continue;

            std::shared_ptr <Pair> pair(
                new Pair(pairInfo["id"], pairInfo["symbol"], base, quote));
            pairContainer.add(pair);
        }
    }
}

void CryptoAPIManager::getExchangeList() {
    networkManager->fetchJson(routes->getExchangeListPath());
}

std::shared_ptr <Exchange> CryptoAPIManager::getExchangeBySymbol(QString symbol) {
    return exchangeContainer.getBySymbol(symbol);
}

void CryptoAPIManager::addExchange(QString id, QString name, QString symbol) {
    std::shared_ptr <Exchange> exchange(new Exchange(routes, this, parser, id, name, symbol));
    exchangeContainer.add(exchange);
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