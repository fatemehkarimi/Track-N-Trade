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
    explicit LeafExchange(Routes* api_routes, JsonParser* json_parser,
                        QString exchange_name, QString exchange_symbol);
    QString getName() override;
    QString getSymbol() override;
    void getCoin(QString coin_symbol) override;
    void getCoinList() override;
    void getExchange(QString exchange_name) override;
    void getExchangeList() override;
    
private slots:
    void parseJson(QString url, QJsonObject json);

private:
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    QMap <QString, Coin*> coinList;
    NetworkManager* networkManager;
};

#endif