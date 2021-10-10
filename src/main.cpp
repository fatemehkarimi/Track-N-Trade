#include <QApplication>
#include <data/api_manager_crypto.h>
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
    CryptoAPIManager cryptowatchAPI(&appSettings, &routes, &parser);

    DashboardController controller(&cryptowatchAPI);
    return app.exec();
}