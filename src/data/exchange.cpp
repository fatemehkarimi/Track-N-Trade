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
    network = new NetworkWrapper();

    pricesTracker = std::make_shared <AllPricesTracker> (
        routes, parser,
        this->symbol,
        Settings::App::getInstance()->getAllPriceRefreshRate());

    QObject::connect(
        pricesTracker.get(),
        &AllPricesTracker::pricesUpdated,
        this,
        &Exchange::handlePriceUpdates);

    priceChangesTracker = std::make_shared <AllPriceChangesTracker> (
        routes, parser, 
        this->symbol,
        Settings::App::getInstance()->getAllPriceChangeRefreshRate());

    QObject::connect(
        priceChangesTracker.get(),
        &AllPriceChangesTracker::priceChangesUpdated,
        this,
        &Exchange::handlePriceChangesUpdates);
}

Exchange::~Exchange() {
    delete ohlcTracker;
    ohlcTracker = nullptr;

    delete latestPriceTracker;
    latestPriceTracker = nullptr;

    delete lowestPriceTracker;
    lowestPriceTracker = nullptr;

    delete highestPriceTracker;
    highestPriceTracker = nullptr;

    delete priceChangeTracker;
    priceChangeTracker = nullptr;

    delete network;
    network = nullptr;
}

void Exchange::handleJsonResponse(QString url, QJsonObject json) {
    this->parseJson(url, json);
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

void Exchange::getOHLCAsync(int period, QDateTime after, QDateTime before) {
    ohlcTracker->getOHLCAsync(period, after, before);
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
    network->fetchJson(routes->getExchangePairsPath(symbol), this);
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

void Exchange::registerOHLCObserver(OHLCObserver* observer) {
    if(ohlcTracker == nullptr)
        return;
    ohlcTracker->registerObserver(observer);
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

void Exchange::createLatestPriceTracker(std::shared_ptr <Pair> pair) {
    latestPriceTracker = new LatestPriceTracker(routes, parser, getSymbol(),
        pair, Settings::App::getInstance()->getSinglePriceRefreshRate());

    QObject::connect(latestPriceTracker, &LatestPriceTracker::priceUpdated,
        this, &Exchange::handleSinglePairPriceUpdate);
}

void Exchange::createPriceChangeTracker(std::shared_ptr <Pair> pair) {
    priceChangeTracker = new PriceChangeTracker(routes,
        parser, getSymbol(), pair,
        Settings::App::getInstance()->getSinglePriceChangeRefreshRate());

    QObject::connect(priceChangeTracker,
        &PriceChangeTracker::priceChangeUpdated, this,
        &Exchange::handleSinglePairPriceChangeUpdate);
}

void Exchange::createLowestPriceTracker(std::shared_ptr <Pair> pair) {
    lowestPriceTracker = new LowestPriceTracker(routes, parser, getSymbol(),
        pair, Settings::App::getInstance()->getSinglePairLowestPriceRefreshRate());

    QObject::connect(lowestPriceTracker, &LowestPriceTracker::lowestPriceUpdated,
        this, &Exchange::handleLowestPriceUpdate);
}

void Exchange::createHighestPriceTracker(std::shared_ptr <Pair> pair) {
    highestPriceTracker = new HighestPriceTracker(routes, parser, getSymbol(),
        pair, Settings::App::getInstance()->getSinglePairHighestPriceRefreshRate());

    QObject::connect(highestPriceTracker, &HighestPriceTracker::highestPriceUpdated,
        this, &Exchange::handleHighestPriceUpdate);
}

void Exchange::createOHLCTracker(std::shared_ptr <Pair> pair) {
    ohlcTracker = new OHLCTracker(routes, parser, getSymbol(), pair);
}

void Exchange::activateOHLCTracker(std::shared_ptr <Pair> pair) {
    createOHLCTracker(pair);
}

void Exchange::activateLatestPriceTracker(std::shared_ptr <Pair> pair) {
    createLatestPriceTracker(pair);
    latestPriceTracker->run();
}

void Exchange::activateLowestPriceTracker(std::shared_ptr <Pair> pair) {
    createLowestPriceTracker(pair);
    lowestPriceTracker->run();
}

void Exchange::activateHighestPriceTracker(std::shared_ptr <Pair> pair) {
    createHighestPriceTracker(pair);
    highestPriceTracker->run();
}

void Exchange::activatePriceChangeTracker(std::shared_ptr <Pair> pair) {
    createPriceChangeTracker(pair);
    priceChangeTracker->run();
}

void Exchange::deactivateOHLCTracker() {
    delete ohlcTracker;
    ohlcTracker = nullptr;
}

void Exchange::deactivateLatestPriceTracker() {
    delete latestPriceTracker;
    latestPriceTracker = nullptr;
}

void Exchange::deactivateLowestPriceTracker() {
    delete lowestPriceTracker;
    lowestPriceTracker = nullptr;
}

void Exchange::deactivateHighestPriceTracker() {
    delete highestPriceTracker;
    highestPriceTracker = nullptr;
}

void Exchange::deactivatePriceChangeTracker() {
    delete priceChangeTracker;
    priceChangeTracker = nullptr;
}

void Exchange::handleSinglePairPriceUpdate(Price price) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyPriceUpdate(latestPriceTracker->getPair(), price);
}

void Exchange::handleSinglePairPriceChangeUpdate(PriceChange priceChange) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyPriceChangeUpdate(
            priceChangeTracker->getPair(), priceChange);
}

void Exchange::handleLowestPriceUpdate(Price price) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyLowestPriceUpdate(
            lowestPriceTracker->getPair(), price);
}

void Exchange::handleHighestPriceUpdate(Price price) {
    for(auto observer : singlePairPriceObservers)
        observer->notifyHighestPriceUpdate(
            highestPriceTracker->getPair(), price);
}
