#include <QApplication>
#include <window/main_window.h>
#include <settings/settings_window.h>

#include <data/api_cryptowatch.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Settings::Window window_settings(0.8, 0.8);
    MainWindow main_window(&window_settings);
    CryptowatchApi api;
    main_window.show();
    return app.exec();
}