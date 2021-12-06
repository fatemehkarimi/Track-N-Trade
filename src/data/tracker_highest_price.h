#ifndef TRACKER_HIGHEST_PRICE_H
#define TRACKER_HIGHEST_PRICE_H

#include "pair.h"
#include "price.h"
#include "routes.h"
#include "parser_json.h"
#include "tracker_market.h"

class HighestPriceTracker : public MarketTracker
{
    Q_OBJECT
public:
    HighestPriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);
    
    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    void getHighestPriceAsync();
    Price getHighestPrice();
    std::shared_ptr <Pair> getPair();

signals:
    void highestPriceUpdated(Price price);

private:
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    Price highestFetchedPrice;
};

#endif