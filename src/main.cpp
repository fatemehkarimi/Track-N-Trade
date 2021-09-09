#include <QApplication>
#include <window/main_window.h>
#include <settings/settings_window.h>

#include <data/exchange_composite.h>
#include <data/routes_cryptowatch.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CryptowatchRoutes routes;
    CompositeExchange exchangeModel(&routes);

    Settings::Window window_settings(0.8, 0.8);
    MainWindow main_window(&window_settings, &exchangeModel);
    main_window.show();
    return app.exec();
}