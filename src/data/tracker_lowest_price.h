#ifndef TRACKER_LOWEST_PRICE_H
#define TRACKER_LOWEST_PRICE_H

#include "pair.h"
#include "price.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"
#include <network/network_manager.h>

class LowestPriceTracker : public Tracker 
{
    Q_OBJECT
public:
    LowestPriceTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);
    
    void performAction() override;
    void getLowestPriceAsync();
    Price getLowestPrice();
    std::shared_ptr <Pair> getPair();

private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void lowestPriceUpdated(Price price);

private:
    Routes* routes;
    JsonParser* parser;
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    NetworkManager* networkManager;
    Price lowestFetchedPrice;
};


#endif