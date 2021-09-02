#include <QScreen>
#include <QGuiApplication>

#include "settings_window.h"

Settings::Window::Window(double width_ratio, double height_ratio) {
    w_ratio = width_ratio;
    h_ratio = height_ratio;

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeo = screen->geometry();
    int height = (int)screenGeo.height() * h_ratio;
    int width = (int)screenGeo.width() * w_ratio;
    size = QSize(width, height);
}

QSize Settings::Window::windowSize() {
    return size;
}