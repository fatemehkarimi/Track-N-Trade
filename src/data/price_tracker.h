#ifndef PRICE_TRACKER_H
#define PRICE_TRACKER_H

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

    PriceTracker(Routes* apiRoutes, JsonParser* jsonParser, QTime watchPeriod);
    void stop();
    void run();
    STATE getState();

private slots:
    void parseJson(QString url, QJsonObject json);
    void fetchItems();
    void fetchPrices();
    void fetchChanges();

signals:
    void pricesUpdated(QMap <QString, QMap <QString, Price> >);
    void priceChangesUpdated(QMap <QString, QMap <QString, Price> >);

private:
    Routes* routes;
    JsonParser* parser;
    STATE state = STATE::STOPPED;
    QTimer timer;
    int watchPeriod; //watch period in msecs
    NetworkManager* networkManager;
    QMap <QString, QMap <QString, Price> > prices;
};

#endif
