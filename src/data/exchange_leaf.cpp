#include <QtConcurrent>
#include "exchange_leaf.h"

LeafExchange::LeafExchange(APIManager* refAPI,Routes* apiRoutes,
        JsonParser* jsonParser, QString exchangeName, QString exchangeSymbol)
    : refAPI(refAPI),
    name(exchangeName),
    symbol(exchangeSymbol),
    routes(apiRoutes),
    parser(jsonParser) {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
                    this, &LeafExchange::parseJson);
}

void LeafExchange::parseJson(QString url, QJsonObject json) {
    if(url == routes->getExchangeMarketsPath(symbol)){
        assetList.clear();
        QFuture < QList <QString> > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangeMarketsJson, json);
        
        QList <QString> symbolList = future.result();
        for(int i = 0; i < symbolList.size(); ++i) {
            std::shared_ptr <Asset> asset = refAPI->getAsset(symbolList[i]);
            if(asset != nullptr)
                assetList[asset->getSymbol()] = asset;
        }
        emit assetListReady(assetList);
    }
}

QString LeafExchange::getName() {
    return name;
}

QString LeafExchange::getSymbol() {
    return symbol;
}

std::shared_ptr <Asset> LeafExchange::getAsset(QString assetSymbol) {
    return assetList[assetSymbol];
}

void LeafExchange::getAssetList() {
    networkManager->fetchJson(routes->getExchangeMarketsPath(symbol));
}
