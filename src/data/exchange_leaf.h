#ifndef EXCHANGE_LEAF_H
#define EXCHANGE_LEAF_H

#include "asset.h"
#include "routes.h"
#include "exchange.h"
#include "parser_json.h"
#include "api_manager.h"
#include <network/network_manager.h>

class LeafExchange : public Exchange
{
public:
    explicit LeafExchange(APIManager* refAPI, Routes* apiRoutes, 
    JsonParser* jsonParser, QString exchangeName, QString exchangeSymbol);

    QString getName() override;
    QString getSymbol() override;
    void getAssetList() override;
    std::shared_ptr <Asset> getAsset(QString assetSymbol) override;
    
private slots:
    void parseJson(QString url, QJsonObject json);

private:
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    APIManager* refAPI;
    QMap <QString, std::shared_ptr <Asset> > assetList;
    NetworkManager* networkManager;
};

#endif