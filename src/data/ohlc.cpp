#include "ohlc.h"

OHLC::OHLC(
    QDateTime closeTime, Price openPrice,
        Price highPrice, Price lowPrice, Price closePrice)
    : closeTime(closeTime),
      openPrice(openPrice),
      highPrice(highPrice),
      lowPrice(lowPrice),
      closePrice(closePrice)
{}

QDateTime OHLC::getCloseTime() {
    return closeTime;
}

Price OHLC::getOpenPrice() {
    return openPrice;
}

Price OHLC::getHighPrice() {
    return highPrice;
}

Price OHLC::getLowPrice() {
    return lowPrice;
}

Price OHLC::getClosePrice() {
    return closePrice;
}