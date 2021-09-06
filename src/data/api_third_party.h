#ifndef API_THIRD_PARTY
#define API_THIRD_PARTY

#include <QList>
#include "api.h"
#include "exchange.h"

class ThirdPartyApi : public Api
{
public:
    virtual Exchange getExchange(QString exchange_symbol) = 0;
    virtual QMap <QString, Exchange> exchangeList() = 0;
};

#endif