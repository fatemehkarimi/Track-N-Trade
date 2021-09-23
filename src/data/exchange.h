#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QMap>
#include <memory>
#include <QString>
#include <QtWidgets>
#include "coin.h"
#include "observer_price.h"

class Exchange : public QObject
{
    Q_OBJECT
public:
    virtual QString getName() = 0;
    virtual QString getSymbol() = 0;
    virtual Coin* getCoin(QString coin_symbol) = 0;
    virtual void getCoinList() = 0;
    virtual std::shared_ptr <Exchange> getExchange(QString exchange_name) = 0;
    virtual void getExchangeList() = 0;
    virtual void addExchange(QString name, QString symbol) = 0;
    virtual void registerPriceObserver(PriceObserver*) = 0;

signals:
    void coinReady(Coin*);
    void coinListReady(QMap <QString, Coin*>);
    void exchangeListReady(QMap <QString, std::shared_ptr <Exchange> >);
};

#endif