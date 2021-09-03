#include <QScreen>
#include <QApplication>
#include "settings_window.h"

Settings::Window::Window(double width_ratio, double height_ratio) {
    w_ratio = width_ratio;
    h_ratio = height_ratio;

    QScreen* screen = (static_cast<QApplication*>(QApplication::instance()))
                            ->screens()[0];
    int height = screen->size().height() * h_ratio;
    int width = screen->size().width() * w_ratio;
    size = QSize(width, height);
}

QSize Settings::Window::windowSize() {
    return size;
}