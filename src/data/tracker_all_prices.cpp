#include <QtConcurrent>
#include "tracker_all_prices.h"


AllPricesTracker::AllPricesTracker(Routes* apiRoutes, JsonParser* parser,
    QString exchangeSymbol, QTime watchPeriod)
    : MarketTracker(apiRoutes, parser, watchPeriod),
      exchangeSymbol(exchangeSymbol)
{}

void AllPricesTracker::performAction() {
    this->getPricesAsync();
}

QMap <QString, Price> AllPricesTracker::getPrices() {
    return prices;
}

void AllPricesTracker::getPricesAsync() {
    if(this->getState() == Tracker::RUNNING) 
        network->fetchJson(routes->getAllPrices(), this);
}

void AllPricesTracker::parseJson(QString url, QJsonObject json) {
    if(this->getState() == Tracker::RUNNING) {
        if(url == routes->getAllPrices()) {
            QFuture < QMap <QString, QMap <QString, double> > > future = 
                QtConcurrent::run(parser, &JsonParser::parseAllPairPrices, json);

            if(this->getState() != Tracker::RUNNING)
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
    }
}
