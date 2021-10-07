#ifndef EXCHANGE_COMPOSITE_H
#define EXCHANGE_COMPOSITE_H

#include <QtWidgets>
#include <QJsonObject>
#include <network/network_manager.h>
#include "routes.h"
#include "exchange.h"
#include "parser_json.h"
#include "price_tracker.h"
#include "observer_price.h"
#include <settings/settings_app.h>

class CompositeExchange : public Exchange
{
    Q_OBJECT
public:
    explicit CompositeExchange(Settings::App* appSettings, 
        Routes* api_routes, JsonParser* parser);
    QString getName() override;
    QString getSymbol() override;
    std::shared_ptr <Coin> getCoin(QString coin_symbol) override;
    void getCoinList() override;
    std::shared_ptr <Exchange> getExchange(QString exchange_name) override;
    void getExchangeList() override;
    void addExchange(QString name, QString symbol) override;
    void clearExchangeList();
    void clearCoinList();
    void registerPriceObserver(PriceObserver*) override;

    friend class JsonParser;

private slots:
    void parseJson(QString, QJsonObject);
    void handlePriceUpdates(QMap <QString, QMap <QString, Price> > prices);
    void handlePriceChangesUpdates(QMap <QString, QMap <QString, Price> > prices);

private:
    Settings::App* appSettings;
    Routes* routes;
    JsonParser* parser;
    PriceTracker* priceTracker;
    //Exchange name, pointer to exchange name
    QMap <QString, std::shared_ptr <Exchange> > exchangeList;
    QMap <QString, std::shared_ptr <Coin> > assets;
    NetworkManager* networkManager;
    QList <PriceObserver*> priceObservers;
};

#endif
