#ifndef EXCHANGE_COMPOSITE_H
#define EXCHANGE_COMPOSITE_H

#include <QtWidgets>
#include <QJsonObject>
#include <network/network_manager.h>
#include "routes.h"
#include "exchange.h"
#include "parser_json.h"

class CompositeExchange : public Exchange
{
    Q_OBJECT
public:
    explicit CompositeExchange(Routes* api_routes, JsonParser* parser);
    QString getName() override;
    QString getSymbol() override;
    void getCoin(QString coin_symbol) override;
    void getCoinList() override;
    Exchange* getExchange(QString exchange_name) override;
    void getExchangeList() override;

    friend class JsonParser;

private slots:
    void parseJson(QString, QJsonObject);

private:
    Routes* routes;
    JsonParser* parser;
    QMap <QString, Exchange*> exchangeList;
    QMap <QString, Coin*> assets;
    NetworkManager* networkManager;

};

#endif
