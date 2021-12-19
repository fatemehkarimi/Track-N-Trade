#ifndef TRACKER_OHLC_H
#define TRACKER_OHLC_H

#include <QDateTime>
#include "pair.h"
#include "routes.h"
#include "tracker.h"
#include "parser_json.h"
#include <network/network_wrapper.h>

class OHLCTracker : public QObject, public NetworkObserver
{
    Q_OBJECT
public:
    OHLCTracker(Routes* routes, JsonParser* parser,
        QString exchangeSymbol, std::shared_ptr <Pair> pair);
    void getOHLCAsync(int period, QDateTime after);
    void getOHLCAsync(int period, QDateTime after, QDateTime before);
    void handleJsonResponse(QString url, QJsonObject json) override;

signals:
    void ohlcUpdated();

private:
    Routes* routes = nullptr;
    JsonParser* parser = nullptr;
    std::shared_ptr <NetworkWrapper> network = nullptr;
    QString exchangeSymbol;
    std::shared_ptr <Pair> pair;
};

#endif
