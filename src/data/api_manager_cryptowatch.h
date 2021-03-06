#ifndef API_MANAGER_CRYPTOWATCH_H
#define API_MANAGER_CRYPTOWATCH_H

#include <QtWidgets>
#include <QJsonObject>
#include <settings/settings_app.h>
#include <network/network_wrapper.h>
#include "routes.h"
#include "api_manager.h"
#include "parser_json.h"
#include "observer_price.h"
#include "container.h"

class CryptoAPIManager : public APIManager, public NetworkObserver
{
    Q_OBJECT
public:
    explicit CryptoAPIManager(Routes* api_routes, JsonParser* parser);
    ~CryptoAPIManager();
    void handleJsonResponse(QString url, QJsonObject json) override;

    void getAssetList() override;
    std::shared_ptr <Asset> getAsset(QString assetSymbol) override;

    void getPairList() override;
    std::shared_ptr <Pair> getPairBySymbol(QString symbol) override;

    void getExchangeList() override;
    std::shared_ptr <Exchange> getExchangeBySymbol(QString symbol) override;


protected:
    void addExchange(QString id, QString name, QString symbol) override;

private slots:
    void parseJson(QString, QJsonObject);

private:
    Settings::App* appSettings;
    Routes* routes;
    JsonParser* parser;
    Container <Exchange> exchangeContainer;
    Container <Asset> assetContainer;
    Container <Pair> pairContainer;
    NetworkWrapper* network = nullptr;
};

#endif
