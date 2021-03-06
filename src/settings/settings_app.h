#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include <QTime>
#include <QString>
#include "settings_font.h"
#include "settings_chart.h"

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

    QTime getSinglePriceRefreshRate() {
        return singlePriceRefreshRate;
    }

    QTime getAllPriceRefreshRate() {
        return allPriceRefreshRate;
    }

    QTime getSinglePriceChangeRefreshRate() {
        return singlePriceChanegRefreshRate;
    }

    QTime getSinglePairLowestPriceRefreshRate() {
        return singleLowestPriceRefreshRate;
    }

    QTime getSinglePairHighestPriceRefreshRate() {
        return singleHighestPriceRefreshRate;
    }

    QTime getAllPriceChangeRefreshRate() {
        return allPriceChangeRefreshRate;
    }

    Settings::Font& getFontSettings() {
        return fontSettings;
    }

    Settings::Chart& getChartSettings() {
        return chartSettings;
    }

private:
    explicit App(){}

    // the name of default exchange on application startup.
    QString defaultExchange = "binance.US";

    // Tracking intervals
    QTime singlePriceRefreshRate = QTime(0, 0, 5);
    QTime singlePriceChanegRefreshRate = QTime(0, 0, 15);
    QTime singleLowestPriceRefreshRate = QTime(0, 1, 0);
    QTime singleHighestPriceRefreshRate = QTime(0, 1, 0);

    QTime allPriceRefreshRate = QTime(0, 0, 20);
    QTime allPriceChangeRefreshRate = QTime(0, 1, 0);

    Settings::Font fontSettings;
    Settings::Chart chartSettings;
};
}

#endif