#ifndef API_CONNECTOR
#define API_CONNECTOR

#include <QMap>
#include <memory>
#include <QString>
#include <QtWidgets>
#include "asset.h"
#include "exchange.h"
#include "observer_price.h"

class APIManager : public QObject {
    Q_OBJECT
public:
    // Assets
    virtual void getAssetList() = 0;
    virtual std::shared_ptr <Asset> getAsset(QString symbol) = 0;

    // Exchanges
    virtual void getExchangeList() = 0;
    virtual void addExchange(QString name, QString symbol) = 0;
    virtual std::shared_ptr <Exchange> getExchange(QString exchangeName) = 0;

    // Registering Observers
    virtual void registerPriceObserver(PriceObserver*) = 0;


signals:
    void assetReady(std::shared_ptr <Asset> );
    void assetListReady(QMap <QString, std::shared_ptr <Asset> >);
    void exchangeListReady(QMap <QString, std::shared_ptr <Exchange> >);
};

#endif