#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(Exchange* refExchange) {
    this->refExchange = refExchange;
    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refExchange);
    view->show();
}

void DashboardController::setExchange(QString exchange_name) {
    selectedExchange = refExchange->getExchange(exchange_name);
    selectedExchange->getCoinList();
    QMetaObject::Connection c = QObject::connect(selectedExchange,
        &Exchange::coinListReady, this, [=](QMap <QString, Coin*> list){
            qDebug() << "coin list updated" << list.size();
        });
}

void DashboardController::exchangeFetched(Exchange* exchange) {
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getCoinList() {
    
}