#include "tracker_ohlc.h"

OHLCTracker::OHLCTracker(Routes* routes, JsonParser* parser,
    QString exchangeSymbol, std::shared_ptr <Pair> pair)
    : routes(routes),
      parser(parser),
      exchangeSymbol(exchangeSymbol),
      pair(pair)
{
    network = std::make_shared <NetworkWrapper>();
}

void OHLCTracker::getOHLCAsync(int period, QDateTime after) {
    network->fetchJson(
        routes->getOHLCPath(
            exchangeSymbol,
            pair->getSymbol(),
            period,
            after.toSecsSinceEpoch()),
        this);
}

void OHLCTracker::getOHLCAsync(int period, QDateTime after, QDateTime before) {
    qDebug() << routes->getOHLCPath(exchangeSymbol, pair->getSymbol(), period, after.toSecsSinceEpoch(), before.toSecsSinceEpoch());
    network->fetchJson(
        routes->getOHLCPath(
            exchangeSymbol,
            pair->getSymbol(),
            period,
            after.toSecsSinceEpoch(),
            before.toSecsSinceEpoch()),
        this);
}

void OHLCTracker::handleJsonResponse(QString url, QJsonObject json) {

}