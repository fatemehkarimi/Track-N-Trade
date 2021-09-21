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
    QObject::connect(&timer, &QTimer::timeout, this, &PriceTracker::fetchPrices);
    fetchPrices();
}

PriceTracker::~PriceTracker() {
    delete this->networkManager;
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
    if(state == STATE::RUNNING) {
        networkManager->fetchJson(routes->getAllPrices());
        timer.start(watchPeriod);
    }
}

void PriceTracker::parseJson(QString url, QJsonObject json) {
    if(state == STATE::RUNNING) {
        QFuture < QMap <QString, QMap <QString, double> > > future = 
            QtConcurrent::run(parser, &JsonParser::parseAllPairPrices, json);

        prices = future.result();
        emit pricesUpdated(prices);
    }
}