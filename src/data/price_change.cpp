#include "price_change.h"

PriceChange::PriceChange(QString exchange, QString pair, double percentage)
    : exchange(exchange),
      pair(pair),
      percentage(percentage)
      {}

PriceChange::PriceChange(const PriceChange& pc) {
    exchange = pc.exchange;
    pair = pc.pair;
    percentage = pc.percentage;
    changeStatus = pc.changeStatus;
}

bool PriceChange::isEmpty() {
    return (exchange.isEmpty() && pair.isEmpty());
}

void PriceChange::updateStatus() {
    if(percentage > 0)
        changeStatus = PriceChange::POSITIVE;
    else if(percentage == 0)
        changeStatus = PriceChange::ZERO;
    else
        changeStatus = PriceChange::NEGATIVE;
}

void PriceChange::update(double percentage) {
    this->percentage = percentage;
    updateStatus();
}

double PriceChange::getChangePercentage() {
    return percentage;
}

QString PriceChange::getExchangeSymbol() {
    return exchange;
}

QString PriceChange::getPairSymbol() {
    return pair;
}

PriceChange::CHANGE_STATUS PriceChange::getStatus() {
    return changeStatus;
}