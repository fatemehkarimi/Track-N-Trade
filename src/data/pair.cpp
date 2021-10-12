#include "pair.h"

Pair::Pair(QString id, QString symbol, Asset base, Asset quote)
    : id(id),
    symbol(symbol),
    base(base),
    quote(quote)
{}

QString Pair::getSymbol() {
    return symbol;
}

Asset Pair::getBase() {
    return base;
}

Asset Pair::getQuote() {
    return quote;
}

QString Pair::getBaseSymbol() {
    return base.getSymbol();
}

QString Pair::getQuoteSymbol() {
    return quote.getSymbol();
}