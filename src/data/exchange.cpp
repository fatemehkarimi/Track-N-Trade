#include <QtConcurrent>
#include "exchange.h"
#include "api_manager.h"

Exchange::Exchange(Routes* apiRoutes, APIManager* refAPI, JsonParser* jsonParser,
        QString id, QString exchangeName, QString exchangeSymbol)
    : id(id),
    name(exchangeName),
    symbol(exchangeSymbol),
    routes(apiRoutes),
    refAPI(refAPI),
    parser(jsonParser) {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &Exchange::parseJson);
}

QString Exchange::getId() {
    return id;
}

QString Exchange::getName() {
    return name;
}

QString Exchange::getSymbol() {
    return symbol;
}

void Exchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangePairsPath(symbol)){
        assetList.clear();
        QFuture < QList <QString> > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangePairsJson, json);
        
        QList <QString> symbolList = future.result();
        for(int i = 0; i < symbolList.size(); ++i) {
            std::shared_ptr <Asset> asset = refAPI->getAsset(symbolList[i]);
            if(asset != nullptr)
                assetList[asset->getSymbol()] = asset;
        }
        emit assetListReady(assetList);
    }
}

std::shared_ptr <Asset> Exchange::getAsset(QString assetSymbol) {
    return assetList[assetSymbol];
}

void Exchange::getAssetList() {
    networkManager->fetchJson(routes->getExchangePairsPath(symbol));
}
