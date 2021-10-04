#ifndef PRICE_H
#define PRICE_H

#include <QtWidgets>
#include <QMetaType>
#include <QString>

class Price {
public:
    Price()
    {}

    Price(QString exchange, QString pair, double latestPrice)
        : exchange(exchange),
          pair(pair),
          price(latestPrice)
          {}

    Price(const Price& p) {
        exchange = p.exchange;
        pair = p.pair;
        price = p.price;
        price_status = p.price_status;
    }



    enum PRICE_STATUS {
        INCREASE,
        NOCHANGE,
        DECREASE
    };

    void updatePrice(double latestPrice);
    QString getExchangeSymbol();
    QString getPairSymbol();
    PRICE_STATUS getPriceStatus();
    double getLatestPrice();

private:
    QString exchange;   // symbol of exchange
    QString pair;       // symbol of pair
    double price = 0;
    PRICE_STATUS price_status = PRICE_STATUS::INCREASE;
};

Q_DECLARE_METATYPE(Price)
#endif