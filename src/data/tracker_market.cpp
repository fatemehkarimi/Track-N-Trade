#include "tracker_market.h"

MarketTracker::MarketTracker(
    Routes* apiRoutes, JsonParser* parser, QTime watchPeriod)
    : routes(apiRoutes),
      parser(parser),
      Tracker(QTime(0, 0, 0).msecsTo(watchPeriod)) {
    network = std::make_shared <NetworkWrapper>();
}

void MarketTracker::handleJsonResponse(QString url, QJsonObject json) {
    this->parseJson(url, json);
}