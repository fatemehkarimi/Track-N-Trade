#include "price.h"


void Price::updatePrice(double latestPrice) {
    if(latestPrice > price)
        price_status = Price::INCREASE;
    else if(latestPrice == price)
        price_status = Price::NOCHANGE;
    else
        price_status = Price::DECREASE;
    price = latestPrice;    
}

QString Price::getExchangeSymbol() {
    return exchange;
}

QString Price::getPairSymbol() {
    return pair;
}

Price::PRICE_STATUS Price::getPriceStatus() {
    return price_status;
}

double Price::getLatestPrice() {
    return price;
}