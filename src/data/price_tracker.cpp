#include <QtConcurrent>
#include "price_tracker.h"


PriceTracker::PriceTracker(Routes* apiRoutes, JsonParser* jsonParser,
    QTime watchPeriod) 
    : routes(apiRoutes),
      parser(jsonParser) {
    this->watchPeriod = QTime(0, 0, 0).msecsTo(watchPeriod);

    this->networkManager = NetworkManager::getInstance();
    QObject::connect(this->networkManager, &NetworkManager::jsonReady,
        this, &PriceTracker::parseJson);
    QObject::connect(&timer, &QTimer::timeout, this, &PriceTracker::fetchItems);
    fetchItems();
}

PriceTracker::~PriceTracker() {
    delete this->networkManager;
}
void PriceTracker::fetchItems() {
    if(state == STATE::RUNNING) {
        fetchPrices();
        fetchChanges();
        timer.start(watchPeriod);
    }
}

void PriceTracker::stop() {
    state = STATE::STOPPED;
    timer.stop();
}

void PriceTracker::run() {
    state = STATE::RUNNING;
    fetchPrices();
}

void PriceTracker::fetchPrices() {
    if(state == STATE::RUNNING) 
        networkManager->fetchJson(routes->getAllPrices());
}

void PriceTracker::fetchChanges() {
    if(state == STATE::RUNNING)
        networkManager->fetchJson(routes->getAll24hSummeries());
}

void PriceTracker::parseJson(QString url, QJsonObject json) {
    if(state == STATE::RUNNING) {
        if(url == routes->getAllPrices()) {
            QFuture < QMap <QString, QMap <QString, double> > > future = 
                QtConcurrent::run(parser, &JsonParser::parseAllPairPrices, json);

            QMap <QString, QMap <QString, double> > result = future.result();
            foreach(const QString& exchange, result.keys())
                foreach(const QString& pair, result[exchange].keys()) {
                    if(prices.contains(exchange) && prices[exchange].contains(pair))
                        prices[exchange].find(pair)->updatePrice(result[exchange][pair]);
                    else {
                        Price price(exchange, pair, result[exchange][pair]);
                        prices[exchange].insert(pair, price);
                    }
                }
            emit pricesUpdated(prices);
        }
        else if(url == routes->getAll24hSummeries()) {
            QFuture < QMap <QString, QMap <QString, double> > > future = 
                QtConcurrent::run(parser, &JsonParser::parseAllPriceChanges, json);

                QMap <QString, QMap <QString, double> > result = future.result();
                foreach(const QString& exchange, result.keys())
                    foreach(const QString& pair, result[exchange].keys()) {
                        if(prices.contains(exchange) && prices[exchange].contains(pair))
                            prices[exchange].find(pair)->setChangePercentage(result[exchange][pair]);
                    }
            emit priceChangesUpdated(prices);
        }
    }
}