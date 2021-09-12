#include <QApplication>
#include <data/exchange_composite.h>
#include <data/routes_cryptowatch.h>
#include <data/controller_dashboard.h>
#include <data/parser_cryptowatch.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CryptowatchRoutes routes;
    CryptowatchParser parser;
    CompositeExchange exchangeModel(&routes, &parser);
    DashboardController controller(&exchangeModel);
    return app.exec();
}