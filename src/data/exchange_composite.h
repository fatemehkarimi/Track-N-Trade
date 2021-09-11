#ifndef EXCHANGE_COMPOSITE_H
#define EXCHANGE_COMPOSITE_H

#include <QtWidgets>
#include <QJsonObject>
#include "routes.h"
#include "exchange.h"
#include "network_manager.h"

class CompositeExchange : public Exchange
{
    Q_OBJECT
public:
    explicit CompositeExchange(Routes* api_routes);
    QString getName() override;
    QString getSymbol() override;
    void getCoin(QString coin_symbol) override;
    void getCoinList() override;
    void getExchange(QString exchange_name) override;
    void getExchangeList() override;

private slots:
    void getExchangeListJson(QJsonObject json);
    void getCoinListJson(QJsonObject json);

private:
    Routes* routes;
    QMap <QString, Exchange*> exchangeList;
    QMap <QString, Coin*> assets;
    NetworkManager* networkManager;
};

#endif
