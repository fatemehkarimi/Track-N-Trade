#include <QApplication>
#include <data/api_manager_cryptowatch.h>
#include <data/routes_cryptowatch.h>
#include <data/controller_dashboard.h>
#include <data/parser_cryptowatch.h>
#include <settings/settings_app.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Settings::App* appSettings = Settings::App::getInstance();

    // loading stylesheet file
    QFile stylesheet(":/stylesheets/lightTheme");
    stylesheet.open(QFile::ReadOnly);
    app.setStyleSheet(stylesheet.readAll());
    stylesheet.close();

    //TODO: use a factory to create cryptowatch api
    CryptowatchRoutes routes;
    CryptowatchParser parser;
    CryptoAPIManager cryptowatchAPI(appSettings, &routes, &parser);
    
    DashboardController controller(&cryptowatchAPI);
    return app.exec();
}