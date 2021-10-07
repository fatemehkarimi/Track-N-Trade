#include "coin.h"
#include <QtWidgets>

Coin::Coin(int id, QString name, QString symbol, bool fiat, QString logo_path) {
    _id = id;
    _name = name;
    _symbol = symbol;
    _fiat = fiat;
    _logo.load(logo_path);
}

int Coin::id() {
    return _id;
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
