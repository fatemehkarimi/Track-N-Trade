#include <QtConcurrent>
#include "tracker_lowest_price.h"

LowestPriceTracker::LowestPriceTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : routes(apiRoutes),
      parser(parser),
      exchangeSymbol(exchangeSymbol),
      pair(pair),
      Tracker(QTime(0, 0, 0).msecsTo(watchPeriod))
{
    this->networkManager = NetworkManager::getInstance();
    QObject::connect(this->networkManager, &NetworkManager::jsonReady,
        this, &LowestPriceTracker::parseJson);
    
    lowestFetchedPrice = Price(exchangeSymbol, pair->getSymbol(), 0);
}

void LowestPriceTracker::performAction() {
    this->getLowestPriceAsync();
}

void LowestPriceTracker::getLowestPriceAsync() {
    if(this->getState() == Tracker::RUNNING)
        networkManager->fetchJson(
            routes->getPairLowestPrice(exchangeSymbol, pair->getSymbol()));
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