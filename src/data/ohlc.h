#ifndef OHLC_H
#define OHLC_H

#include <QDateTime>
#include "price.h"


class OHLC
{
public:
    explicit OHLC(
        QDateTime closeTime, Price openPrice,
        Price highPrice, Price lowPrice, Price closePrice);

    QDateTime getCloseTime();
    Price getOpenPrice();
    Price getHighPrice();
    Price getLowPrice();
    Price getClosePrice();
    
private:
    QDateTime closeTime;
    Price openPrice;
    Price highPrice;
    Price lowPrice;
    Price closePrice;
};

#endif