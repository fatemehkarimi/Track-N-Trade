#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include <QTime>
#include <QString>
#include "settings_font.h"

namespace Settings
{
class App {
public:
    static App* getInstance() {
        static App appSettings;
        return &appSettings;
    }

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

    Settings::Font& getFontSettings() {
        return fontSettings;
    }

private:
    explicit App(){}

    // the name of default exchange on application startup.
    QString defaultExchange = "binance.US";

    // price tracker's timer interval in secs.
    QTime priceRefreshRate = QTime(0, 0, 20);

    Settings::Font fontSettings;
};
}

#endif