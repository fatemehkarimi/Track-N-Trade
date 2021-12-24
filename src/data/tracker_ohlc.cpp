#include <QtConcurrent>
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
    QFuture <QList <OHLC> > future = 
        QtConcurrent::run(parser, &JsonParser::parseOHLC, json);
    QList <OHLC> result = future.result();
    foreach(OHLC ohlcData, result) {
        Price openPrice(
            exchangeSymbol,
            pair->getSymbol(),
            ohlcData.getOpenPrice().getLatestPrice());

        Price highPrice(
            exchangeSymbol,
            pair->getSymbol(),
            ohlcData.getHighPrice().getLatestPrice());
        
        Price lowPrice(
            exchangeSymbol,
            pair->getSymbol(),
            ohlcData.getLowPrice().getLatestPrice());
        
        Price closePrice(
            exchangeSymbol,
            pair->getSymbol(),
            ohlcData.getClosePrice().getLatestPrice());

        ohlcData.setOpenPrice(openPrice);
        ohlcData.setClosePrice(closePrice);
        ohlcData.setLowPrice(lowPrice);
        ohlcData.setClosePrice(closePrice);
    }
    emit ohlcUpdated(result);
}