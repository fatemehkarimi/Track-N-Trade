#ifndef TRACKER_LATEST_PRICE_H
#define TRACKER_LATEST_PRICE_H

#include "pair.h"
#include "price.h"
#include "tracker_market.h"


class LatestPriceTracker : public MarketTracker
{
    Q_OBJECT
public:
    LatestPriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);

    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    void getPriceAsync();
    Price getPrice();
    std::shared_ptr <Pair> getPair();

signals:
    void priceUpdated(Price price);

private:
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    Price latestFetchedPrice;
};

#endif