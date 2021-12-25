#ifndef SETTINGS_CHART_H
#define SETTINGS_CHART_H

#include <QtWidgets>

namespace Settings {
class Chart {
public:
    explicit Chart();
    QColor getIncreasingColor();
    QColor getDecreasingColor();

private:
    QColor increaseColor = QColor(70, 203, 130);
    QColor decreaseColor = QColor(217, 61, 74);
};
}

#endif