#ifndef TRACKER_OHLC_H
#define TRACKER_OHLC_H

#include <QList>
#include <QDateTime>
#include <network/network_wrapper.h>
#include "pair.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"
#include "observer_ohlc.h"

class OHLCTracker : public QObject, public NetworkObserver
{
    Q_OBJECT
public:
    OHLCTracker(Routes* routes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair);

    void getOHLCAsync(int period, QDateTime after);
    void getOHLCAsync(int period, QDateTime after, QDateTime before);
    void handleJsonResponse(QString url, QJsonObject json) override;
    void registerObserver(OHLCObserver* observer);

private:
    void notifyObservers(QList <OHLC>);

    Routes* routes = nullptr;
    JsonParser* parser = nullptr;
    std::shared_ptr <Pair> pair;
    QString exchangeSymbol;
    std::shared_ptr <NetworkWrapper> network = nullptr;
    QList <OHLCObserver*> observerList;
};

#endif
