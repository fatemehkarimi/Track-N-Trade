#include "coin.h"

Coin::Coin(QString name, QString symbol, bool fiat, QString logo_path) {
    _name = name;
    _symbol = symbol;
    _fiat = fiat;
    _logo.load(logo_path);
}

QString Coin::name() {
    return _name;
}

QString Coin::symbol() {
    return _symbol;
}

QPixmap Coin::logo() {
    return _logo;
}