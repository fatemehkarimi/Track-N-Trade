#ifndef API_CRYPTOWATCH_H
#define API_CRYPTOWATCH_H

#include "api_third_party.h"
#include "config_cryptowatch.h"

class CryptowatchApi : public ThirdPartyApi
{
public:
    explicit CryptowatchApi();
    Exchange currentExchange() override;
    void setExchangeByName(QString name) override;
    QList <Exchange> exchangeList() override;

private:
    QList <Exchange> exchange_list;
};

#endif