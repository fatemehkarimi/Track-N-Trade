#include <QApplication>
#include <data/exchange_composite.h>
#include <data/routes_cryptowatch.h>
#include <data/controller_dashboard.h>
#include <data/parser_cryptowatch.h>
#include <settings/settings_app.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Settings::App appSettings;

    //TODO: use a factory to create cryptowatch api
    CryptowatchRoutes routes;
    CryptowatchParser parser;

    CompositeExchange exchangeModel(&appSettings, &routes, &parser);
    DashboardController controller(&exchangeModel);
    return app.exec();
}