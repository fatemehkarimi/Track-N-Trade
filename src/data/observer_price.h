#ifndef OBSERVER_PRICE_H
#define OBSERVER_PRICE_H

class PriceObserver
{
public:
    virtual void getPriceUpdates(QMap <QString, QMap <QString, double> > prices) = 0;
};

#endif