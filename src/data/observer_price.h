#ifndef OBSERVER_PRICE_H
#define OBSERVER_PRICE_H

#include "price.h"

class PriceObserver
{
public:
    virtual void getPriceUpdates(QMap <QString, QMap <QString, Price> > prices) = 0;
    virtual void getPriceChangesUpdates(QMap <QString, QMap <QString, Price> > prices) = 0;
};

#endif