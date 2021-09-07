#ifndef EXCHANGE_COMPOSITE_H
#define EXCHANGE_COMPOSITE_H

#include <QString>
#include "routes.h"
#include "exchange.h"

class CompositeExchange : public Exchange
{
public:
    explicit CompositeExchange(Routes* api_routes);
    QString getName() override;
    QString getSymbol() override;
    void getCoin() override;
    void getCoinList() override;
    void getDefaultExchange() override;
    void setDefaultExchange(QString exchange_symbol) override;
    void getExchange(QString exchange_symbol) override;
    void getExchangeList() override;

private:
    Routes* routes;
    QMap <QString, Exchange*> exchangeList;
};

#endif
