#ifndef TRACKER_PRICE_H
#define TRACKER_PRICE_H

#include <memory>
#include <network/network_manager.h>
#include "pair.h"
#include "price.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"


class PriceTracker : public Tracker
{
    Q_OBJECT
public:
    PriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);

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
    NetworkManager* networkManager;
    Price latestFetchedPrice;
};

#endif