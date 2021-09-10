#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(Exchange* refExchange) {
    this->refExchange = refExchange;
    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, refExchange);
    view->show();
}

void DashboardController::setExchange(QString exchange_name) {
    QObject::connect(refExchange, &Exchange::exchangeReady,
                    this, &DashboardController::exchangeFetched);
    refExchange->getExchange(exchange_name);
}

void DashboardController::exchangeFetched(Exchange* exchange) {
    QObject::connect(refExchange, &Exchange::exchangeReady,
                    this, &DashboardController::exchangeFetched);
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getCoinList() {
    
}