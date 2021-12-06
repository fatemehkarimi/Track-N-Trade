#include <QtConcurrent>
#include "tracker_lowest_price.h"

LowestPriceTracker::LowestPriceTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : MarketTracker(apiRoutes, parser, watchPeriod),
      exchangeSymbol(exchangeSymbol),
      pair(pair)
{
    lowestFetchedPrice = Price(exchangeSymbol, pair->getSymbol(), 0);
}

void LowestPriceTracker::performAction() {
    this->getLowestPriceAsync();
}

void LowestPriceTracker::getLowestPriceAsync() {
    if(this->getState() == Tracker::RUNNING)
        network->fetchJson(
            routes->getPairLowestPrice(exchangeSymbol, pair->getSymbol()), this);
}

Price LowestPriceTracker::getLowestPrice() {
    return lowestFetchedPrice;
}

std::shared_ptr <Pair> LowestPriceTracker::getPair() {
    return pair;
}

void LowestPriceTracker::parseJson(QString url, QJsonObject json) {
    if(this->getState() == Tracker::RUNNING) {
        if(url == routes->getPairLowestPrice(exchangeSymbol, pair->getSymbol())) {
            QFuture <double> future = QtConcurrent::run(
                parser, &JsonParser::parsePairLowestPrice, json);

            if(this->getState() != Tracker::RUNNING)
                return;
            
            double result = future.result();
            lowestFetchedPrice.updatePrice(result);
            emit lowestPriceUpdated(lowestFetchedPrice);
        }
    }
}