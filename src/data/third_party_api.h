#ifndef THIRD_PARTY_API
#define THIRD_PARTY_API

#include <QList>
#include "api.h"
#include "exchange.h"

class ThirdPartyApi : public Api
{
public:
    virtual Exchange currentExchange() = 0;
    virtual void setExchangeByName(QString name) = 0;
    virtual QList <Exchange> exchangeList() = 0;
};

#endif