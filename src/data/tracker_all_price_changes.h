#ifndef TRACKER_ALL_PRICE_CHANGES_H
#define TRACKER_ALL_PRICE_CHANGES_H

#include <QTime>
#include <QtConcurrent>
#include <network/network_wrapper.h>
#include "price_change.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"

class AllPriceChangesTracker : public Tracker, public NetworkObserver
{
    Q_OBJECT
public:
    AllPriceChangesTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, QTime watchPeriod);
    ~AllPriceChangesTracker();
    
    void handleJsonResponse(QString url, QJsonObject json) override;

    void performAction() override;
    QMap <QString, PriceChange> getPriceChanges();
    void getPriceChangesAsync();

private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void priceChangesUpdated(QMap <QString, PriceChange>);

private:
    Routes* routes;
    JsonParser* parser;
    QString exchangeSymbol;
    NetworkWrapper* network = nullptr;
    QMap <QString, PriceChange> priceChanges;    
};

#endif
