#ifndef EXCHANGE_LEAF_H
#define EXCHANGE_LEAF_H

#include "coin.h"
#include "routes.h"
#include "exchange.h"
#include "parser_json.h"
#include <network/network_manager.h>

class LeafExchange : public Exchange
{
public:
    explicit LeafExchange(Exchange* parent, Routes* api_routes, 
    JsonParser* json_parser, QString exchange_name, QString exchange_symbol);
    ~LeafExchange();

    QString getName() override;
    QString getSymbol() override;
    Coin* getCoin(QString coin_symbol) override;
    void getCoinList() override;
    Exchange* getExchange(QString exchange_name) override;
    void getExchangeList() override;
    void addExchange(QString name, QString symbol) override;
    void registerPriceObserver(PriceObserver*) override;
    
private slots:
    void parseJson(QString url, QJsonObject json);

private:
    Exchange* parent;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    QMap <QString, Coin*> coinList;
    NetworkManager* networkManager;
};

#endif