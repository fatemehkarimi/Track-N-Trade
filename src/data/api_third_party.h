#ifndef API_THIRD_PARTY
#define API_THIRD_PARTY

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