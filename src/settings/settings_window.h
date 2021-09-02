#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QSize>

namespace Settings {
class Window {
public:
    Window(double width_ratio, double height_ratio);
    QSize windowSize();

private:
    QSize size;
    double h_ratio;
    double w_ratio;
};
}

#endif