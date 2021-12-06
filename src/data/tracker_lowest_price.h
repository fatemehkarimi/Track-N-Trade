#ifndef TRACKER_LOWEST_PRICE_H
#define TRACKER_LOWEST_PRICE_H

#include "pair.h"
#include "price.h"
#include "tracker_market.h"

class LowestPriceTracker : public MarketTracker
{
    Q_OBJECT
public:
    LowestPriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);
    
    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    void getLowestPriceAsync();
    Price getLowestPrice();
    std::shared_ptr <Pair> getPair();

signals:
    void lowestPriceUpdated(Price price);

private:
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    Price lowestFetchedPrice;
};


#endif