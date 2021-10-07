#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include "exchange.h"

class Controller
{
public:
    virtual void setExchange(QString exchange_name) = 0;
    virtual void getAssetList() = 0;
};

#endif