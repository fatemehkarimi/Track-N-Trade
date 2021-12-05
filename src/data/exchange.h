#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <network/network_wrapper.h>
#include "pair.h"
#include "asset.h"
#include "routes.h"
#include "api_item.h"
#include "container.h"
#include "parser_json.h"
#include "observer_price.h"
#include "observer_single_pair_price.h"
#include "tracker_latest_price.h"
#include "tracker_lowest_price.h"
#include "tracker_all_prices.h"
#include "tracker_price_change.h"
#include "tracker_all_price_changes.h"

class APIManager;

class Exchange : public APIItem, public NetworkObserver
{
    Q_OBJECT
public:
    explicit Exchange(Routes* apiRoutes, APIManager* refAPI,
        JsonParser* jsonParser, QString id, QString exchangeName,
        QString exchangeSymbol);
    ~Exchange();
    
    void handleJsonResponse(QString url, QJsonObject json) override;

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
    void createLowestPriceTracker(std::shared_ptr <Pair>);

    void deleteSinglePairPriceTracker();
    void deleteSinglePairPriceChangeTracker();
    void deleteLowestPriceTracker();

    void handleSinglePairPriceUpdate(Price price);
    void handleSinglePairPriceChangeUpdate(PriceChange priceChange);
    void handleLowestPriceUpdate(Price price);

    void handlePriceUpdates(QMap <QString, Price> prices);
    void handlePriceChangesUpdates(QMap <QString, PriceChange> priceChanges);

    QString id;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    APIManager* refAPI;
    Container <Pair> pairContainer;
    NetworkWrapper* network = nullptr;
    QList <PriceObserver*> priceObservers;
    QList <SinglePairPriceObserver*> singlePairPriceObservers;

    LatestPriceTracker* singlePairPriceTracker = nullptr;
    LowestPriceTracker* lowestPriceTracker = nullptr;
    AllPricesTracker* pricesTracker = nullptr;
    PriceChangeTracker* singlePairPriceChangeTracker = nullptr;
    AllPriceChangesTracker* priceChangesTracker = nullptr;
};

#endif