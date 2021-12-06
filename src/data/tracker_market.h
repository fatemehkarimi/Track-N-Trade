#ifndef TRACKER_MARKET_H
#define TRACKER_MARKET_H

#include <memory>
#include <network/network_wrapper.h>
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"

class MarketTracker : public Tracker, public NetworkObserver
{
public:
    MarketTracker(
        Routes* apiRoutes, JsonParser* parser, QTime watchPeriod);
    
    void handleJsonResponse(QString url, QJsonObject json) override;
    virtual void parseJson(QString url, QJsonObject json) = 0;

protected:
    Routes* routes = nullptr;
    JsonParser* parser = nullptr;
    std::shared_ptr <NetworkWrapper> network = nullptr;
};

#endif