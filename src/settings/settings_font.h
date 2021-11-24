#ifndef SETTINGS_FONT_H
#define SETTINGS_FONT_H

#include <QtWidgets>
#include <QFont>

#define RALEWAY "Raleway-Regular"
#define ROBOTOCONDENSED "Roboto Condensed"
#define OPENSANSCONDENSED "Open Sans Condensed"

namespace Settings {
class Font
{
public:
    explicit Font();
    // Market table
    QFont getMarketTablePairFont();
    QFont getMarketTablePriceFont();
    QFont getMarketTablePriceChangeFont();
    QFont getExchangeMenuFont();

    // Price table
    QFont getPriceTableAssetFont();
    QFont getPriceTablePriceFont();
    QFont getPriceTablePriceChangeFont();

private:
    int largeFontSize = 32;
    int normalFontSize = 14;
    int smallFontSize = 9;
};
}

#endif