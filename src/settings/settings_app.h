#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include <QTime>
#include <QString>

namespace Settings
{
class App {
public:

    QString getDefaultExchange() {
        return defaultExchange;
    }

    void setDefaultExchange(QString exchangeName) {
        defaultExchange = exchangeName;
    }

    QTime getPriceRefreshRate() {
        return priceRefreshRate;
    }

    void setPriceRefreshRate(QTime interval) {
        priceRefreshRate = interval;
    }

private:
    // the name of default exchange on application startup.
    QString defaultExchange = "binance.US";

    // price tracker's timer interval in secs.
    QTime priceRefreshRate = QTime(0, 0, 20);
};
}

#endif