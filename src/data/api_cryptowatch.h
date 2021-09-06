#ifndef API_CRYPTOWATCH_H
#define API_CRYPTOWATCH_H

#include <QStack>
#include "json_receiver.h"
#include "api_third_party.h"
#include "network_manager.h"
#include "config_cryptowatch.h"

class CryptowatchApi : public JsonReceiver,
    public ThirdPartyApi
{
    Q_OBJECT
public:
    explicit CryptowatchApi();
    Exchange currentExchange() override;
    void setExchangeByName(QString name) override;
    QList <Exchange> exchangeList() override;

private slots:
    void exchangeListReady(QJsonObject);

private:
    void getExchangeList();

    CryptowatchConfig api_config;
    NetworkManager* network_manager;
    QList <Exchange> exchange_list;
    QStack <QMetaObject::Connection> connection_list;
};

#endif