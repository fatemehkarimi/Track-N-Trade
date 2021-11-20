#include <QtConcurrent>
#include "exchange.h"
#include "api_manager.h"
#include <settings/settings_app.h>

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

    pricesTracker = new AllPricesTracker(routes, parser,
        this->symbol, Settings::App::getInstance()->getPriceRefreshRate());

    QObject::connect(pricesTracker, &AllPricesTracker::pricesUpdated,
        this, &Exchange::handlePriceUpdates);

    priceChangesTracker = new AllPriceChangesTracker(routes, parser, 
        this->symbol, Settings::App::getInstance()->getPriceChangesRefreshRate());

    QObject::connect(priceChangesTracker,
        &AllPriceChangesTracker::priceChangesUpdated, this,
        &Exchange::handlePriceChangesUpdates);
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

QMap <QString, Price> Exchange::getPrices() {
    return pricesTracker->getPrices();
}

QMap <QString, Price> Exchange::getPriceChanges() {
    return priceChangesTracker->getPriceChanges();
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

void Exchange::activateTracking() {
    if(priceChangesTracker->getState() != Tracker::RUNNING)
        priceChangesTracker->run();

    if(pricesTracker->getState() != Tracker::RUNNING)
        pricesTracker->run();
}

void Exchange::deactivateTracking() {
    priceObservers.clear();
    if(priceChangesTracker->getState() != Tracker::STOPPED)
        priceChangesTracker->stop();

    if(pricesTracker->getState() != Tracker::STOPPED)
        pricesTracker->stop();
}

void Exchange::registerPriceObserver(PriceObserver* observer) {
    this->priceObservers.append(observer);
}

void Exchange::handlePriceUpdates(QMap <QString, Price> prices) {
    for(auto observer : priceObservers)
        observer->notifyPriceUpdates();
}

void Exchange::handlePriceChangesUpdates(QMap <QString, Price> prices) {
    for(auto observer : priceObservers)
        observer->notifyPriceChangeUpdates();
}
