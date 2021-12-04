#ifndef TRACKER_ALL_PRICES_H
#define TRACKER_ALL_PRICES_H

#include <QTime>
#include <network/network_wrapper.h>
#include "price.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"

class AllPricesTracker : public Tracker, public NetworkObserver
{
    Q_OBJECT
public:
    AllPricesTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, QTime watchPeriod);
    void handleJsonResponse(QString url, QJsonObject json) override;
    
    void performAction() override;
    QMap <QString, Price> getPrices();
    void getPricesAsync();

private slots:
    void parseJson(QString url, QJsonObject json);

signals:
    void pricesUpdated(QMap <QString, Price>);

private:
    Routes* routes;
    JsonParser* parser;
    QString exchangeSymbol;
    NetworkWrapper* network = nullptr;
    QMap <QString, Price> prices;
};

#endif
