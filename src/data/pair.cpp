#include "pair.h"

Pair::Pair(QString id, QString symbol, std::shared_ptr <Asset> base,
        std::shared_ptr <Asset> quote)
    : id(id),
    symbol(symbol),
    base(base),
    quote(quote)
{}

QString Pair::getId() {
    return id;
}

QString Pair::getSymbol() {
    return symbol;
}

std::shared_ptr <Asset> Pair::getBase() {
    return base;
}

std::shared_ptr <Asset> Pair::getQuote() {
    return quote;
}

QString Pair::getBaseSymbol() {
    return base->getSymbol();
}

QString Pair::getQuoteSymbol() {
    return quote->getSymbol();
}