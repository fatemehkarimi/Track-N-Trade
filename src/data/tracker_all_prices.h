/*
#ifndef TRACKER_PRICE_H
#define TRACKER_PRICE_H

#include <QTime>
#include <network/network_manager.h>
#include "routes.h"
#include "parser_json.h"
#include "price.h"

class PriceTracker : public QObject
{
    Q_OBJECT
public:
    enum STATE {
        STOPPED,
        RUNNING
    };

    PriceTracker(Routes* apiRoutes, JsonParser* jsonParser,
        QString exchangeSymbol, QTime watchPeriod);
    void stop();
    void run();
    STATE getState();
    QMap <QString, Price> getPrices();

private slots:
    void parseJson(QString url, QJsonObject json);
    void getItemsAsync();
    void getPricesAsync();
    void getChangesAsync();

signals:
    void pricesUpdated(QMap <QString, Price>);
    void priceChangesUpdated(QMap <QString, Price>);

private:
    Routes* routes;
    JsonParser* parser;
    STATE state = STATE::STOPPED;
    QString exchangeSymbol;
    QTimer timer;
    int watchPeriod; //watch period in msecs
    NetworkManager* networkManager;
    QMap <QString, Price> prices;
};

#endif

*/