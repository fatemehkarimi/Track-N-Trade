#include <QApplication>
#include <window/main_window.h>
#include <settings/settings_window.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Settings::Window window_settings(0.8, 0.8);
    MainWindow main_window(&window_settings);
    main_window.show();
    return app.exec();
}