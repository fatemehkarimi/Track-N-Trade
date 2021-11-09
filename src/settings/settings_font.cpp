#include "settings_font.h"

Settings::Font::Font() {
    QFontDatabase::addApplicationFont(":/fonts/Raleway-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/RobotoCondensed-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/OpenSans_Condensed-Regular.ttf");
}

QFont Settings::Font::getMarketTablePairFont() {
    return QFont(OPENSANSCONDENSED, normalFontSize, QFont::Normal);
}

QFont Settings::Font::getMarketTablePriceFont() {
    return QFont(ROBOTOCONDENSED, normalFontSize, QFont::Normal);
}

QFont Settings::Font::getMarketTablePriceChangeFont() {
    return QFont(ROBOTOCONDENSED, normalFontSize, QFont::Normal);
}

QFont Settings::Font::getExchangeMenuFont() {
    return QFont(OPENSANSCONDENSED, normalFontSize, QFont::Normal);    
}