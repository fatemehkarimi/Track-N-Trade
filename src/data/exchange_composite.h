#ifndef EXCHANGE_COMPOSITE_H
#define EXCHANGE_COMPOSITE_H

#include <QtWidgets>
#include <QJsonObject>
#include "routes.h"
#include "exchange.h"
#include "network_manager.h"
#include "json_receiver.h"

class CompositeExchange : public Exchange,
    public JsonReceiver
{
public:
    explicit CompositeExchange(Routes* api_routes);
    QString getName() override;
    QString getSymbol() override;
    void getCoin(QString coin_symbol) override;
    void getCoinList() override;
    void getDefaultExchange() override;
    void setDefaultExchange(QString exchange_symbol) override;
    void getExchange(QString exchange_symbol) override;
    void getExchangeList() override;

private slots:
    void getExchangeListJson(QJsonObject json);

private:
    Routes* routes;
    QMap <QString, Exchange*> exchangeList;
    NetworkManager* networkManager;
};

#endif
