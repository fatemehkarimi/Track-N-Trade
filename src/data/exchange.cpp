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
        this->symbol, Settings::App::getInstance()->getAllPriceRefreshRate());

    QObject::connect(pricesTracker, &AllPricesTracker::pricesUpdated,
        this, &Exchange::handlePriceUpdates);

    priceChangesTracker = new AllPriceChangesTracker(routes, parser, 
        this->symbol, Settings::App::getInstance()->getAllPriceChangeRefreshRate());

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

QMap <QString, PriceChange> Exchange::getPriceChanges() {
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

void Exchange::activateAllPairTracking() {
    if(priceChangesTracker->getState() != Tracker::RUNNING)
        priceChangesTracker->run();

    if(pricesTracker->getState() != Tracker::RUNNING)
        pricesTracker->run();
}

void Exchange::deactivateAllPairTracking() {
    priceObservers.clear();
    singlePairPriceObservers.clear();
    if(priceChangesTracker->getState() != Tracker::STOPPED)
        priceChangesTracker->stop();

    if(pricesTracker->getState() != Tracker::STOPPED)
        pricesTracker->stop();
}

void Exchange::registerPriceObserver(PriceObserver* observer) {
    this->priceObservers.append(observer);
}

void Exchange::registerSinglePairPriceObserver(SinglePairPriceObserver* observer) {
    this->singlePairPriceObservers.append(observer);
}

void Exchange::handlePriceUpdates(QMap <QString, Price> prices) {
    for(auto observer : priceObservers)
        observer->notifyPriceUpdates();
}

void Exchange::handlePriceChangesUpdates(QMap <QString, PriceChange> priceChanges) {
    for(auto observer : priceObservers)
        observer->notifyPriceChangeUpdates();
}

void Exchange::createSinglePairPriceTracker(std::shared_ptr <Pair> pair) {
    singlePairPriceTracker = new LatestPriceTracker(routes, parser, getSymbol(),
        pair, Settings::App::getInstance()->getSinglePriceRefreshRate());
    QObject::connect(singlePairPriceTracker, &LatestPriceTracker::priceUpdated,
        this, &Exchange::handleSinglePairPriceUpdate);
}

void Exchange::createSinglePairPriceChangeTracker(std::shared_ptr <Pair> pair) {
    singlePairPriceChangeTracker = new PriceChangeTracker(routes,
        parser, getSymbol(), pair,
        Settings::App::getInstance()->getSinglePriceChangeRefreshRate());
    QObject::connect(singlePairPriceChangeTracker,
        &PriceChangeTracker::priceChangeUpdated, this,
        &Exchange::handleSinglePairPriceChangeUpdate);
}

void Exchange::createLowestPriceTracker(std::shared_ptr <Pair> pair) {
    lowestPriceTracker = new LowestPriceTracker(routes, parser, getSymbol(),
        pair, Settings::App::getInstance()->getSinglePairLowestPriceRefreshRate());
    QObject::connect(lowestPriceTracker, &LowestPriceTracker::lowestPriceUpdated,
        this, &Exchange::handleLowestPriceUpdate);
}

void Exchange::activateSinglePairTracking(std::shared_ptr <Pair> pair) {
    deactivateSinglePairTracking();
    this->createSinglePairPriceTracker(pair);
    singlePairPriceTracker->run();

    this->createSinglePairPriceChangeTracker(pair);
    singlePairPriceChangeTracker->run();

    this->createLowestPriceTracker(pair);
    lowestPriceTracker->run();
}

void Exchange::deleteSinglePairPriceTracker() {
    if(singlePairPriceTracker == nullptr)
        return;
    QObject::disconnect(singlePairPriceTracker);
    delete singlePairPriceTracker;
    singlePairPriceTracker = nullptr;
}

void Exchange::deleteSinglePairPriceChangeTracker() {
    if(singlePairPriceChangeTracker == nullptr)
        return;
    QObject::disconnect(singlePairPriceChangeTracker);
    delete singlePairPriceChangeTracker;
    singlePairPriceChangeTracker = nullptr;
}

void Exchange::deleteLowestPriceTracker() {
    if(lowestPriceTracker == nullptr)
        return;
    QObject::disconnect(lowestPriceTracker);
    delete lowestPriceTracker;
    lowestPriceTracker = nullptr;
}

void Exchange::deactivateSinglePairTracking() {
    deleteSinglePairPriceTracker();
    deleteSinglePairPriceChangeTracker();
    deleteLowestPriceTracker();
}

void Exchange::handleSinglePairPriceUpdate(Price price) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyPriceUpdate(singlePairPriceTracker->getPair(), price);
}

void Exchange::handleSinglePairPriceChangeUpdate(PriceChange priceChange) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyPriceChangeUpdate(
            singlePairPriceChangeTracker->getPair(), priceChange);
}

void Exchange::handleLowestPriceUpdate(Price price) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyLowestPriceUpdate(
            lowestPriceTracker->getPair(), price);
}