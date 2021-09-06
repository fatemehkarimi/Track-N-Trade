#include "exchange.h"

Exchange::Exchange(QString name, QString symbol) {
    _name = name;
    _symbol = symbol;
}

QString Exchange::name() {
    return _name;
}

QString Exchange::symbol() {
    return _symbol;
}

Coin Exchange::getCoin(QString coin_name) {
    //find coin and return;
}

QList <Coin> Exchange::coinList() {
    return _coinList;
}