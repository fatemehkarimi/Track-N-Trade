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

private:
    int normalFontSize = 14;
};
}

#endif