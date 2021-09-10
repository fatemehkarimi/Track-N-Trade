#include <QApplication>
#include <data/exchange_composite.h>
#include <data/routes_cryptowatch.h>
#include <data/controller_dashboard.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CryptowatchRoutes routes;
    CompositeExchange exchangeModel(&routes);
    DashboardController controller(&exchangeModel);
    return app.exec();
}