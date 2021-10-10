#include <QtConcurrent>
#include "exchange.h"

Exchange::Exchange(Routes* apiRoutes, JsonParser* jsonParser,
        QString id, QString exchangeName, QString exchangeSymbol)
    : id(id),
    name(exchangeName),
    symbol(exchangeSymbol),
    routes(apiRoutes),
    parser(jsonParser) {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &Exchange::parseJson);
}

QString Exchange::getName() {
    return name;
}

QString Exchange::getSymbol() {
    return symbol;
}

void Exchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeMarketsPath(symbol)){
        // assetList.clear();
        // QFuture < QList <QString> > future = QtConcurrent::run(parser,
        //     &JsonParser::parseExchangeMarketsJson, json);
        
        // QList <QString> symbolList = future.result();
        // for(int i = 0; i < symbolList.size(); ++i) {
        //     std::shared_ptr <Asset> asset = refAPI->getAsset(symbolList[i]);
        //     if(asset != nullptr)
        //         assetList[asset->getSymbol()] = asset;
        // }
        // emit assetListReady(assetList);
    }
}

std::shared_ptr <Asset> Exchange::getAsset(QString assetSymbol) {
    return assetList[assetSymbol];
}

void Exchange::getAssetList() {
    networkManager->fetchJson(routes->getExchangeMarketsPath(symbol));
}
