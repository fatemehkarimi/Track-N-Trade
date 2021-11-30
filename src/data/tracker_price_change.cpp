#include <QtConcurrent>
#include "tracker_price_change.h"


PriceChangeTracker::PriceChangeTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod)
    : routes(apiRoutes),
      parser(parser),
      exchangeSymbol(exchangeSymbol),
      pair(pair),
      Tracker(QTime(0, 0, 0).msecsTo(watchPeriod))
{
    this->networkManager = NetworkManager::getInstance();
    QObject::connect(this->networkManager, &NetworkManager::jsonReady,
        this, &PriceChangeTracker::parseJson);
    priceChange = PriceChange(exchangeSymbol, pair->getSymbol(), 0);
}

void PriceChangeTracker::performAction() {
    this->getPriceChangeAsync();
}

void PriceChangeTracker::getPriceChangeAsync() {
    if(this->getState() == Tracker::RUNNING)
        networkManager->fetchJson(
            routes->getPairPriceChange(exchangeSymbol, pair->getSymbol()));
}

PriceChange PriceChangeTracker::getPriceChange() {
    return priceChange;
}

std::shared_ptr <Pair> PriceChangeTracker::getPair() {
    return this->pair;
}

void PriceChangeTracker::parseJson(QString url, QJsonObject json) {
    if(this->getState() == Tracker::RUNNING) {
        if(url == routes->getPairPriceChange(exchangeSymbol, pair->getSymbol())) {
            QFuture <double> future = QtConcurrent::run(
                parser, &JsonParser::parsePairPriceChange, json);

            if(this->getState() != Tracker::RUNNING)
                return;
            
            double result = future.result();
            priceChange.update(result);
            emit priceChangeUpdated(priceChange);
        }
    }
}