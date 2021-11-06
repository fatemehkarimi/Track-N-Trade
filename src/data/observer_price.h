#ifndef OBSERVER_PRICE_H
#define OBSERVER_PRICE_H

#include "price.h"

class PriceObserver
{
public:
    virtual void notifyPriceUpdates() = 0;
    virtual void notifyPriceChangeUpdates() = 0;
};

#endif