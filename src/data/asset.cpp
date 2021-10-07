#include "asset.h"
#include <QtWidgets>

Asset::Asset(int id, QString name, QString symbol, bool fiat, QString logo_path) {
    _id = id;
    _name = name;
    _symbol = symbol;
    _fiat = fiat;
    _logo.load(logo_path);
}

int Asset::getId() {
    return _id;
}

QString Asset::getName() {
    return _name;
}

QString Asset::getSymbol() {
    return _symbol;
}

QPixmap Asset::getLogo() {
    return _logo;
}
