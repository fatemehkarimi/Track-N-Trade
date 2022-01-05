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

QFont Settings::Chart::getChartLabelFont() {
    return QFont(ROBOTOCONDENSED, 12, QFont::Normal);
}

QFont Settings::Chart::getIntervalButtonFont() {
    return QFont(ROBOTOCONDENSED, 12, QFont::Normal);
}