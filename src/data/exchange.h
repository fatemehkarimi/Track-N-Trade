#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "pair.h"
#include "asset.h"
#include "routes.h"
#include "api_item.h"
#include "container.h"
#include "parser_json.h"
#include "observer_price.h"
#include "observer_single_pair_price.h"
#include "tracker_price.h"
#include "tracker_all_prices.h"
#include "tracker_price_change.h"
#include "tracker_all_price_changes.h"
#include <network/network_manager.h>

class APIManager;

class Exchange : public APIItem
{
    Q_OBJECT
public:
    explicit Exchange(Routes* apiRoutes, APIManager* refAPI,
        JsonParser* jsonParser, QString id, QString exchangeName,
        QString exchangeSymbol);

    QString getId() override;
    QString getSymbol() override;
    QString getName();
    void getPairList();
    QMap <QString, Price> getPrices();
    QMap <QString, PriceChange> getPriceChanges();
    std::shared_ptr <Pair> getPair(QString symbol);
    void activateAllPairTracking();
    void deactivateAllPairTracking();
    void activateSinglePairTracking(std::shared_ptr <Pair> pair);
    void deactivateSinglePairTracking();
    void registerPriceObserver(PriceObserver* observer);
    void registerSinglePairPriceObserver(SinglePairPriceObserver* observer);
    
private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void pairListReady(Container <Pair>);

private:
    void createSinglePairPriceTracker(std::shared_ptr <Pair>);
    void createSinglePairPriceChangeTracker(std::shared_ptr <Pair>);

    void deleteSinglePairPriceTracker();
    void deleteSinglePairPriceChangeTracker();

    void handleSinglePairPriceUpdate(Price price);
    void handleSinglePairPriceChangeUpdate(PriceChange priceChange);

    void handlePriceUpdates(QMap <QString, Price> prices);
    void handlePriceChangesUpdates(QMap <QString, PriceChange> priceChanges);

    QString id;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    APIManager* refAPI;
    Container <Pair> pairContainer;
    NetworkManager* networkManager;
    QList <PriceObserver*> priceObservers;
    QList <SinglePairPriceObserver*> singlePairPriceObservers;

    PriceTracker* singlePairPriceTracker = nullptr;
    AllPricesTracker* pricesTracker = nullptr;
    PriceChangeTracker* singlePairPriceChangeTracker = nullptr;
    AllPriceChangesTracker* priceChangesTracker = nullptr;
};

#endif