#ifndef EXCHANGE_LEAF_H
#define EXCHANGE_LEAF_H

#include "routes.h"
#include "exchange.h"
#include "network_manager.h"

class LeafExchange : public Exchange
{
public:
    explicit LeafExchange(Routes* api_routes,
                        QString exchange_name, QString exchange_symbol);
    QString getName() override;
    QString getSymbol() override;
    void getCoin(QString coin_symbol) override;
    void getCoinList() override;
    void getExchange(QString exchange_name) override;
    void getExchangeList() override;
    
private slots:
    void getCoinListJson(QJsonObject json);

private:
    QString name;
    QString symbol;
    Routes* routes;
    NetworkManager* networkManager;
};

#endif