#ifndef TRACKER_PRICE_CHANGE_H
#define TRACKER_PRICE_CHANGE_H

#include "pair.h"
#include "price_change.h"
#include "tracker_market.h"

class PriceChangeTracker : public MarketTracker
{
    Q_OBJECT
public:
    PriceChangeTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);

    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    void getPriceChangeAsync();
    PriceChange getPriceChange();
    std::shared_ptr <Pair> getPair();

signals:
    void priceChangeUpdated(PriceChange priceChange);

private:
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    PriceChange priceChange;
};

#endif