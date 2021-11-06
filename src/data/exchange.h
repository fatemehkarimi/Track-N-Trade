#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "pair.h"
#include "asset.h"
#include "routes.h"
#include "api_item.h"
#include "container.h"
#include "parser_json.h"
#include "price_tracker.h"
#include "observer_price.h"
#include <network/network_manager.h>

class APIManager;

class Exchange : public QObject, public APIItem
{
    Q_OBJECT
public:
    explicit Exchange(Routes* apiRoutes, APIManager* refAPI, JsonParser* jsonParser,
        QString id, QString exchangeName, QString exchangeSymbol);

    QString getId() override;
    QString getSymbol() override;
    QString getName();
    void getPairList();
    std::shared_ptr <Pair> getPair(QString symbol);
    void activatePriceTracker();
    void deactivatePriceTracker();
    void registerPriceObserver(PriceObserver* observer);
    
private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void pairListReady(Container <Pair>);

private:
    QString id;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    APIManager* refAPI;
    PriceTracker* priceTracker;
    Container <Pair> pairContainer;
    NetworkManager* networkManager;
    QList <PriceObserver*> priceObservers;

    void handlePriceUpdates(QMap <QString, Price> prices);
    void handlePriceChangesUpdates(QMap <QString, Price> prices);
};

#endif