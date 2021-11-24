#include <QtConcurrent>
#include "tracker_price.h"

PriceTracker::PriceTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : routes(apiRoutes),
      parser(parser),
      exchangeSymbol(exchangeSymbol),
      pair(pair),
      Tracker(QTime(0, 0, 0).msecsTo(watchPeriod))
{
    this->networkManager = NetworkManager::getInstance();
    QObject::connect(this->networkManager, &NetworkManager::jsonReady,
        this, &PriceTracker::parseJson);
    latestFetchedPrice = Price(exchangeSymbol, pair->getSymbol(), 0);
}

void PriceTracker::performAction() {
    this->getPriceAsync();
}

void PriceTracker::getPriceAsync() {
    if(this->getState() == Tracker::RUNNING)
        networkManager->fetchJson(
            routes->getPairPrice(exchangeSymbol, pair->getSymbol()));
}

Price PriceTracker::getPrice() {
    return latestFetchedPrice;
}

std::shared_ptr <Pair> PriceTracker::getPair() {
    return this->pair;
}

void PriceTracker::parseJson(QString url, QJsonObject json) {
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