#include <iostream>
#include <QApplication>
#include <settings/settings_window.h>

int main(int argc, char* argv[]) {
    Settings::Window window_settings(0.5, 0.5);
    QApplication app(argc, argv);
    return app.exec();
}