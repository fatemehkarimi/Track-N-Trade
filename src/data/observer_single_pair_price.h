#ifndef OBSERVER_SINGLE_PAIR_PRICE_H
#define OBSERVER_SINGLE_PAIR_PRICE_H

#include "pair.h"
#include "price.h"
#include "price_change.h"

class SinglePairPriceObserver
{
public:
    virtual void notifyPriceUpdate(std::shared_ptr <Pair> pair, Price price) = 0;
    virtual void notifyPriceChangeUpdate(std::shared_ptr <Pair> pair, PriceChange priceChange) = 0;
    virtual void notifyLowestPriceUpdate(std::shared_ptr <Pair> pair, Price price) = 0;
};

#endif