#include "exchange.h"

Exchange::Exchange(QString name, QList <Coin> coin_list) {
    _name = name;
    _coinList = coin_list;
}

QString Exchange::name() {
    return _name;
}

Coin Exchange::getCoin(QString coin_name) {
    //find coin and return;
}

QList <Coin> Exchange::coinList() {
    return _coinList;
}