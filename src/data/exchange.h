#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "asset.h"
#include "routes.h"
#include "parser_json.h"
#include <network/network_manager.h>
#include "api_item.h"

class APIManager;

class Exchange : public QObject, public APIItem
{
    Q_OBJECT
public:
    explicit Exchange(Routes* apiRoutes, APIManager* refAPI, JsonParser* jsonParser,
        QString id, QString exchangeName, QString exchangeSymbol);

    QString getId() override;
    QString getSymbol() override;
    QString getName();
    void getAssetList();
    std::shared_ptr <Asset> getAsset(QString assetSymbol);
    
private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void assetListReady(QMap <QString, std::shared_ptr <Asset> >);

private:
    QString id;
    QString name;
    QString symbol;
    Routes* routes;
    JsonParser* parser;
    APIManager* refAPI;
    QMap <QString, std::shared_ptr <Asset> > assetList;
    NetworkManager* networkManager;
};

#endif