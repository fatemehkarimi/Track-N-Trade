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

QFont Settings::Font::getPriceTableAssetFont() {
    return QFont(OPENSANSCONDENSED, largeFontSize, QFont::Normal);
}

QFont Settings::Font::getPriceTablePriceFont() {
    return QFont(ROBOTOCONDENSED, largeFontSize, QFont::Normal);
}

QFont Settings::Font::getPriceTablePriceChangeFont() {
    return QFont(ROBOTOCONDENSED, normalFontSize, QFont::Normal);
}

QFont Settings::Font::getPriceTableLowestPriceFont() {
    return QFont(ROBOTOCONDENSED, normalFontSize, QFont::Normal);
}

QFont Settings::Font::getPriceTableHighestPriceFont() {
    return QFont(ROBOTOCONDENSED, normalFontSize, QFont::Normal);
}