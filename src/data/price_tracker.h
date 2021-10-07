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
    PriceTracker(Routes* apiRoutes, JsonParser* jsonParser, QTime watchPeriod);
    ~PriceTracker();
    void stop();
    void run();

    enum STATE {
        STOPPED,
        RUNNING
    };

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
    STATE state = STATE::RUNNING;
    QTimer timer;
    int watchPeriod; //watch period in msecs
    NetworkManager* networkManager;
    QMap <QString, QMap <QString, Price> > prices;
};

#endif
