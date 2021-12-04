#ifndef TRACKER_LATEST_PRICE_H
#define TRACKER_LATEST_PRICE_H

#include <memory>
#include <network/network_wrapper.h>
#include "pair.h"
#include "price.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"


class LatestPriceTracker : public Tracker, public NetworkObserver
{
    Q_OBJECT
public:
    LatestPriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);
    ~LatestPriceTracker();

    void handleJsonResponse(QString url, QJsonObject json) override;
    void performAction() override;
    void getPriceAsync();
    Price getPrice();
    std::shared_ptr <Pair> getPair();

private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void priceUpdated(Price price);

private:
    Routes* routes;
    JsonParser* parser;
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    NetworkWrapper* network;
    Price latestFetchedPrice;
};

#endif