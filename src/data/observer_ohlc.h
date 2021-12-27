#ifndef OBSERVER_OHLC_H
#define OBSERVER_OHLC_H

#include <memory>
#include <QList>
#include "ohlc.h"
#include "pair.h"

class OHLCObserver {
public:
    virtual void notifyOHLCUpdate(std::shared_ptr <Pair> pair, QList <OHLC> ohlcData) = 0;
};


#endif