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
        pairContainer.clearAll();
        QFuture < QList <QString> > future = QtConcurrent::run(parser,
            &JsonParser::parseExchangePairsJson, json);
        
        QList <QString> symbolList = future.result();
        for(int i = 0; i < symbolList.size(); ++i) {
            std::shared_ptr <Pair> pair = refAPI->getPairBySymbol(symbolList[i]);
            if(pair != nullptr) {
                //only pairs with quote = usd are allowed
                if(pair->getQuoteSymbol() != "usd")
                    continue;
                pairContainer.add(pair);
            }
        }
        emit pairListReady(pairContainer);
    }
}

std::shared_ptr <Pair> Exchange::getPair(QString symbol) {
    return pairContainer.getBySymbol(symbol);
}

void Exchange::getPairList() {
    networkManager->fetchJson(routes->getExchangePairsPath(symbol));
}
