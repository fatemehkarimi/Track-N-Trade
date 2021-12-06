#ifndef TRACKER_ALL_PRICE_CHANGES_H
#define TRACKER_ALL_PRICE_CHANGES_H

#include <QTime>
#include <QtConcurrent>
#include "tracker_market.h"
#include "price_change.h"

class AllPriceChangesTracker : public MarketTracker
{
    Q_OBJECT
public:
    AllPriceChangesTracker(Routes* apiRoutes, JsonParser* parser,
        QString exchangeSymbol, QTime watchPeriod);
    
    void performAction() override;
    void parseJson(QString url, QJsonObject json) override;
    QMap <QString, PriceChange> getPriceChanges();
    void getPriceChangesAsync();

signals:
    void priceChangesUpdated(QMap <QString, PriceChange>);

private:
    QString exchangeSymbol;
    QMap <QString, PriceChange> priceChanges;    
};

#endif
