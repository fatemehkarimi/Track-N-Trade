#include "asset.h"
#include <QtWidgets>

Asset::Asset(QString id, QString name, QString symbol, bool fiat, QString logo_path)
    : id(id),
    name(name),
    symbol(symbol),
    fiat(fiat) {
    logo.load(logo_path);
}

QString Asset::getId() {
    return id;
}

QString Asset::getName() {
    return name;
}

QString Asset::getSymbol() {
    return symbol;
}

QPixmap Asset::getLogo() {
    return logo;
}
