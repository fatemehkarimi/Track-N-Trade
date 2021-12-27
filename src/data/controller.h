#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include "exchange.h"

class Controller
{
public:
    virtual void setExchange(QString exchangeName) = 0;
    virtual void handlePairSelected(QString pairSymbol) = 0;
    virtual void getAssetList() = 0;
};

#endif