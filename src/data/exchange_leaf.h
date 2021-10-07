#ifndef EXCHANGE_LEAF_H
#define EXCHANGE_LEAF_H

#include "asset.h"
#include "routes.h"
#include "exchange.h"
#include "parser_json.h"
#include <network/network_manager.h>

class LeafExchange : public Exchange
{
public:
    explicit LeafExchange(Exchange* parent, Routes* api_routes, 
    JsonParser* json_parser, QString exchange_name, QString exchange_symbol);

    QString getName() override;
    QString getSymbol() override;
    std::shared_ptr <Asset> getAsset(QString assetSymbol) override;
    void getAssetList() override;
    std::shared_ptr <Exchange> getExchange(QString exchangeName) override;
    void getExchangeList() override;
    void addExchange(QString name, QString symbol) override;
    void registerPriceObserver(PriceObserver*) override;
    
private slots:
    void parseJson(QString url, QJsonObject json);

private:
    Exchange* parent;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    QMap <QString, std::shared_ptr <Asset> > assetList;
    NetworkManager* networkManager;
};

#endif