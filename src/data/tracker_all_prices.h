#ifndef TRACKER_ALL_PRICES_H
#define TRACKER_ALL_PRICES_H

#include <QTime>
#include "tracker_market.h"
#include "price.h"

class AllPricesTracker : public MarketTracker
{
    Q_OBJECT
public:
    AllPricesTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, QTime watchPeriod);
    
    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    QMap <QString, Price> getPrices();
    void getPricesAsync();

signals:
    void pricesUpdated(QMap <QString, Price>);

private:
    QString exchangeSymbol;
    QMap <QString, Price> prices;
};

#endif
