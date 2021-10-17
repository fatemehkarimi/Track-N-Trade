#ifndef API_CONNECTOR
#define API_CONNECTOR

#include <QMap>
#include <memory>
#include <QString>
#include <QtWidgets>
#include "pair.h"
#include "asset.h"
#include "exchange.h"
#include "observer_price.h"
#include "container.h"

class APIManager : public QObject {
    Q_OBJECT
public:
    // Assets
    virtual void getAssetList() = 0;
    virtual std::shared_ptr <Asset> getAsset(QString symbol) = 0;

    // Pairs
    virtual void getPairList() = 0;
    virtual std::shared_ptr <Pair> getPair(QString symbol) = 0;

    // Exchanges
    virtual void getExchangeList() = 0;
    virtual void addExchange(QString id, QString name, QString symbol) = 0;
    virtual std::shared_ptr <Exchange> getExchangeBySymbol(QString symbol) = 0;

    // Registering Observers
    virtual void registerPriceObserver(PriceObserver*) = 0;

signals:
    void assetReady(std::shared_ptr <Asset> );
    void assetListReady(Container <Asset> assetContainer);
    void pairListReady(Container <Pair> pairContainer);
    void exchangeListReady(Container <Exchange> exchangeContainer);
};

#endif