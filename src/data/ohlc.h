#ifndef OHLC_H
#define OHLC_H

#include <QDateTime>
#include "price.h"


class OHLC
{
public:
    explicit OHLC();
    OHLC(
        QDateTime closeTime, Price openPrice,
        Price highPrice, Price lowPrice, Price closePrice);

    QDateTime setCloseTime(QDateTime closeTime);
    void setOpenPrice(Price openPrice);
    void setHighPrice(Price highPrice);
    void setLowPrice(Price lowPrice);
    void setClosePrice(Price closePrice);

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