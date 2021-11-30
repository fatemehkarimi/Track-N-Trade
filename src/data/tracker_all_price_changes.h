#ifndef TRACKER_ALL_PRICE_CHANGES_H
#define TRACKER_ALL_PRICE_CHANGES_H

#include <QTime>
#include <QtConcurrent>
#include <network/network_manager.h>
#include "price_change.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"

class AllPriceChangesTracker : public Tracker
{
    Q_OBJECT
public:
    AllPriceChangesTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, QTime watchPeriod);

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
    NetworkManager* networkManager;
    QMap <QString, PriceChange> priceChanges;    
};

#endif
