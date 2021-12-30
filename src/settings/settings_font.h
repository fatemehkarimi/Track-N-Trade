#ifndef SETTINGS_FONT_H
#define SETTINGS_FONT_H

#include <QtWidgets>
#include <QFont>
#include "settings_constants.h"


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
    QFont getPriceTableLowestPriceFont();
    QFont getPriceTableHighestPriceFont();

private:
    int largeFontSize = 32;
    int normalFontSize = 14;
    int smallFontSize = 9;
};
}

#endif