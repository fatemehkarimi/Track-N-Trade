#include "pair.h"

Pair::Pair(QString symbol, Coin base, Coin quote)
    : symbol(symbol),
    base(base),
    quote(quote)
{}

QString Pair::getSymbol() {
    return symbol;
}

Coin Pair::getBaseCoin() {
    return base;
}

Coin Pair::getQuoteCoin() {
    return quote;
}

QString Pair::getBaseSymbol() {
    return base.symbol();
}

QString Pair::getQuoteSymbol() {
    return quote.symbol();
}