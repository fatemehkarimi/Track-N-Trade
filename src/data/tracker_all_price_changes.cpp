#include "tracker_all_price_changes.h"

AllPriceChangesTracker::AllPriceChangesTracker(Routes* apiRoutes,
    JsonParser* parser, QString exchangeSymbol,QTime watchPeriod)
    : MarketTracker(apiRoutes, parser, watchPeriod),
      exchangeSymbol(exchangeSymbol)
{}

void AllPriceChangesTracker::performAction() {
    this->getPriceChangesAsync();
}

void AllPriceChangesTracker::getPriceChangesAsync() {
    if(this->getState() == Tracker::RUNNING)
        network->fetchJson(routes->getAllPriceChanges(), this);
}

QMap <QString, PriceChange> AllPriceChangesTracker::getPriceChanges() {
    return priceChanges;
}

void AllPriceChangesTracker::parseJson(QString url, QJsonObject json) {
    if(url == routes->getAllPriceChanges()) {
        QFuture < QMap <QString, QMap <QString, double> > > future = 
            QtConcurrent::run(parser, &JsonParser::parseAllPriceChanges, json);

        if(this->getState() != Tracker::RUNNING)
            return;

        QMap <QString, QMap <QString, double> > result = future.result();
        foreach(const QString& pair, result[exchangeSymbol].keys()) {
            if(priceChanges.contains(pair))
                priceChanges.find(pair)->update(
                    result[exchangeSymbol][pair]);
            else {
                PriceChange priceChange(exchangeSymbol, pair, result[exchangeSymbol][pair]);
                priceChanges.insert(pair, priceChange);
            }
        }
        emit priceChangesUpdated(priceChanges);
    }
}
