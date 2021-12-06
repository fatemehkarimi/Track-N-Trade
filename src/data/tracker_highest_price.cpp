#include <QtConcurrent>
#include "tracker_highest_price.h"

HighestPriceTracker::HighestPriceTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : MarketTracker(apiRoutes, parser, watchPeriod),
      exchangeSymbol(exchangeSymbol),
      pair(pair)
{
    highestFetchedPrice = Price(exchangeSymbol, pair->getSymbol(), 0);
}

void HighestPriceTracker::performAction() {
    this->getHighestPriceAsync();
}

void HighestPriceTracker::getHighestPriceAsync() {
    if(this->getState() == Tracker::RUNNING)
        network->fetchJson(
            routes->getPairHighestPrice(exchangeSymbol, pair->getSymbol()), this);
}

Price HighestPriceTracker::getHighestPrice() {
    return highestFetchedPrice;
}

std::shared_ptr <Pair> HighestPriceTracker::getPair() {
    return pair;
}

void HighestPriceTracker::parseJson(QString url, QJsonObject json) {
    if(this->getState() == Tracker::RUNNING) {
        if(url == routes->getPairHighestPrice(exchangeSymbol, pair->getSymbol())) {
            QFuture <double> future = QtConcurrent::run(
                parser, &JsonParser::parsePairHighestPrice, json);

            if(this->getState() != Tracker::RUNNING)
                return;
            
            double result = future.result();
            highestFetchedPrice.updatePrice(result);
            emit highestPriceUpdated(highestFetchedPrice);
        }
    }
}