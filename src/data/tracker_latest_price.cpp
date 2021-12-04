#include <QtConcurrent>
#include "tracker_latest_price.h"

LatestPriceTracker::LatestPriceTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : routes(apiRoutes),
      parser(parser),
      exchangeSymbol(exchangeSymbol),
      pair(pair),
      Tracker(QTime(0, 0, 0).msecsTo(watchPeriod))
{
    network = new NetworkWrapper();
}

LatestPriceTracker::~LatestPriceTracker() {
    delete network;
    network = nullptr;
}

void LatestPriceTracker::handleJsonResponse(QString url, QJsonObject json) {
    this->parseJson(url, json);
}

void LatestPriceTracker::performAction() {
    this->getPriceAsync();
}

void LatestPriceTracker::getPriceAsync() {
    if(this->getState() == Tracker::RUNNING)
        network->fetchJson(
            routes->getPairPrice(exchangeSymbol, pair->getSymbol()), this);
}

Price LatestPriceTracker::getPrice() {
    return latestFetchedPrice;
}

std::shared_ptr <Pair> LatestPriceTracker::getPair() {
    return this->pair;
}

void LatestPriceTracker::parseJson(QString url, QJsonObject json) {
    if(this->getState() == Tracker::RUNNING) {
        if(url == routes->getPairPrice(exchangeSymbol, pair->getSymbol())) {
            QFuture <double> future = QtConcurrent::run(
                parser, &JsonParser::parsePairPrice, json);

            if(this->getState() != Tracker::RUNNING)
                return;
            
            double result = future.result();
            latestFetchedPrice.updatePrice(result);
            emit priceUpdated(latestFetchedPrice);
        }
    }
}