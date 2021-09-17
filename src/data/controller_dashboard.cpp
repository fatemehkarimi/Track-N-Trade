#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(Exchange* refExchange) {
    this->refExchange = refExchange;
    refExchange->registerPriceObserver(this);
    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refExchange);
    view->show();
}

void DashboardController::setExchange(QString exchange_name) {
    selectedExchange = refExchange->getExchange(exchange_name);
    selectedExchange->getCoinList();
    QMetaObject::Connection c = QObject::connect(selectedExchange,
        &Exchange::coinListReady, this, [=](QMap <QString, Coin*> list){
            view->fillCoinTable(list);
        });
}

void DashboardController::exchangeFetched(Exchange* exchange) {
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getCoinList() {
    
}

void DashboardController::getPriceUpdates(
        QMap <QString, QMap <QString, double> > prices) {
}