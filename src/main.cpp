#include <iostream>
#include <QScreen>
#include <QApplication>
#include <settings/settings_window.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Settings::Window window_settings(1, 1);
    return app.exec();
}