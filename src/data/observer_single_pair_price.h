#ifndef OBSERVER_SINGLE_PAIR_PRICE_H
#define OBSERVER_SINGLE_PAIR_PRICE_H

#include "pair.h"
#include "price.h"

class SinglePairPriceObserver
{
public:
    virtual void notifyPriceUpdate(std::shared_ptr <Pair> pair, Price price) = 0;
};

#endif