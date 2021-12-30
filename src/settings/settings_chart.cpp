#include "settings_chart.h"

Settings::Chart::Chart() {}

QColor Settings::Chart::getIncreasingColor() {
    return increaseColor;
}

QColor Settings::Chart::getDecreasingColor() {
    return decreaseColor;
}

QFont Settings::Chart::getChartTitleFont() {
    return QFont(ROBOTOCONDENSED, 32, QFont::Normal);
}