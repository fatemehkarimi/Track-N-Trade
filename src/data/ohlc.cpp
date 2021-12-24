#include "ohlc.h"

OHLC::OHLC() {}

OHLC::OHLC(
    QDateTime closeTime, Price openPrice,
        Price highPrice, Price lowPrice, Price closePrice)
    : closeTime(closeTime),
      openPrice(openPrice),
      highPrice(highPrice),
      lowPrice(lowPrice),
      closePrice(closePrice)
{}

QDateTime OHLC::setCloseTime(QDateTime closeTime) {
    this->closeTime = closeTime;
}

void OHLC::setOpenPrice(Price openPrice) {
    this->openPrice = openPrice;
}

void OHLC::setHighPrice(Price highPrice) {
    this->highPrice = highPrice;
}

void OHLC::setLowPrice(Price lowPrice) {
    this->lowPrice = lowPrice;
}

void OHLC::setClosePrice(Price closePrice) {
    this->closePrice = closePrice;
}

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