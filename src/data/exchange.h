#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QtWidgets>
#include <QMap>
#include <QString>
#include "coin.h"

class Exchange : public QObject
{
    Q_OBJECT
public:
    virtual QString getName() = 0;
    virtual QString getSymbol() = 0;
    virtual void getCoin(QString coin_symbol) = 0;
    virtual void getCoinList() = 0;
    virtual void getExchange(QString exchange_name) = 0;
    virtual void getExchangeList() = 0;

signals:
    void coinReady(Coin*);
    void coinListReady(QMap <QString, Coin*>);
    void exchangeReady(Exchange*);
    void exchangeListReady(QMap <QString, Exchange*>);
};

#endif