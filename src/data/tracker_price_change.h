#ifndef TRACKER_PRICE_CHANGE_H
#define TRACKER_PRICE_CHANGE_H

#include "tracker.h"
#include "routes.h"
#include "pair.h"
#include "parser_json.h"
#include "price_change.h"
#include <network/network_manager.h>

class PriceChangeTracker : public Tracker
{
    Q_OBJECT
public:
    PriceChangeTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair, QTime watchPeriod);

    void performAction() override;
    void getPriceChangeAsync();
    PriceChange getPriceChange();
    std::shared_ptr <Pair> getPair();

private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void priceChangeUpdated(PriceChange priceChange);

private:
    Routes* routes;
    JsonParser* parser;
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
    NetworkManager* networkManager;
    PriceChange priceChange;
};

#endif