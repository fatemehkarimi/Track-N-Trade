#ifndef PRICE_H
#define PRICE_H

#include <QString>

class Price {
public:
    Price(QString exchange, QString pair, double latestPrice)
        : exchange(exchange),
          pair(pair),
          price(latestPrice)
          {}

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
    double price;
    PRICE_STATUS price_status;
};

#endif