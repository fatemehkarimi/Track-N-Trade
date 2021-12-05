#include <QEventLoop>
#include <QtConcurrent>
#include "api_manager_cryptowatch.h"

CryptoAPIManager::CryptoAPIManager(Routes* api_routes, JsonParser* json_parser) {
    routes = api_routes;
    parser = json_parser;

    network = new NetworkWrapper();
    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(this, &CryptoAPIManager::assetListReady,
            this, [=](){
                getPairList();
            });

    getExchangeList();
    getAssetList();
}

CryptoAPIManager::~CryptoAPIManager() {
    delete network;
    network = nullptr;
}

void CryptoAPIManager::handleJsonResponse(QString url, QJsonObject json) {
    this->parseJson(url, json);
}

void CryptoAPIManager::getAssetList() {
    network->fetchJson(routes->getAssets(), this);
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
    network->fetchJson(routes->getPairs(), this);
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
        emit pairListReady(pairContainer);
    }
}

void CryptoAPIManager::getExchangeList() {
    network->fetchJson(routes->getExchangeListPath(), this);
}

std::shared_ptr <Exchange> CryptoAPIManager::getExchangeBySymbol(QString symbol) {
    return exchangeContainer.getBySymbol(symbol);
}

void CryptoAPIManager::addExchange(QString id, QString name, QString symbol) {
    std::shared_ptr <Exchange> exchange(new Exchange(routes, this, parser, id, name, symbol));
    exchangeContainer.add(exchange);
}
