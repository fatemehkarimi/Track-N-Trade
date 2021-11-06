#include <QtConcurrent>
#include "price_tracker.h"


PriceTracker::PriceTracker(Routes* apiRoutes, JsonParser* jsonParser,
    QString exchangeSymbol, QTime watchPeriod) 
    : routes(apiRoutes),
      parser(jsonParser),
      exchangeSymbol(exchangeSymbol) {
    this->watchPeriod = QTime(0, 0, 0).msecsTo(watchPeriod);

    this->networkManager = NetworkManager::getInstance();
    QObject::connect(this->networkManager, &NetworkManager::jsonReady,
        this, &PriceTracker::parseJson);
    QObject::connect(&timer, &QTimer::timeout, this, &PriceTracker::getItemsAsync);
}

void PriceTracker::getItemsAsync() {
    if(state == STATE::RUNNING) {
        getPricesAsync();
        getChangesAsync();
        timer.start(watchPeriod);
    }
}

void PriceTracker::stop() {
    state = STATE::STOPPED;
    timer.stop();
}

void PriceTracker::run() {
    state = STATE::RUNNING;
    getItemsAsync();
}

PriceTracker::STATE PriceTracker::getState() {
    return state;
}

QMap <QString, Price> PriceTracker::getPrices() {
    return prices;
}

void PriceTracker::getPricesAsync() {
    if(state == STATE::RUNNING) 
        networkManager->fetchJson(routes->getAllPrices());
}

void PriceTracker::getChangesAsync() {
    if(state == STATE::RUNNING)
        networkManager->fetchJson(routes->getAll24hSummeries());
}


void PriceTracker::parseJson(QString url, QJsonObject json) {
    if(state == STATE::RUNNING) {
        if(url == routes->getAllPrices()) {
            QFuture < QMap <QString, QMap <QString, double> > > future = 
                QtConcurrent::run(parser, &JsonParser::parseAllPairPrices, json);

            if(state != STATE::RUNNING)
                return;

            QMap <QString, QMap <QString, double> > result = future.result();
            if(result.contains(exchangeSymbol))  {
                foreach(const QString& pair, result[exchangeSymbol].keys())
                    if(prices.contains(pair))
                        prices.find(pair)->updatePrice(result[exchangeSymbol][pair]);
                    else {
                        Price price(exchangeSymbol, pair, result[exchangeSymbol][pair]);
                        prices.insert(pair, price);
                    }
            }
            emit pricesUpdated(prices);
        }
        else if(url == routes->getAll24hSummeries()) {
            QFuture < QMap <QString, QMap <QString, double> > > future = 
                QtConcurrent::run(parser, &JsonParser::parseAllPriceChanges, json);

            if(state != STATE::RUNNING)
                return;

            QMap <QString, QMap <QString, double> > result = future.result();
            foreach(const QString& pair, result[exchangeSymbol].keys()) {
                if(prices.contains(pair))
                    prices.find(pair)->setChangePercentage(result[exchangeSymbol][pair]);
            }
            emit priceChangesUpdated(prices);
        }
    }
}
