#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(Exchange* refExchange) {
    this->refExchange = refExchange;
    refExchange->registerPriceObserver(this);

    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refExchange);
    coin_table = view->getCoinTable();

    view->show();
}

void DashboardController::setExchange(QString exchange_name) {
    selectedExchange = refExchange->getExchange(exchange_name);
    qDebug() << selectedExchange->getName();
    selectedExchange->getCoinList();

    QMetaObject::Connection c = QObject::connect(selectedExchange.get(),
        &Exchange::coinListReady, this, [=](QMap <QString, Coin*> list){
            qDebug() << "coin list ready" << list.size();
            coin_table->clear();
            for(auto itm = list.begin(); itm != list.end(); ++itm)
                coin_table->addCoin(itm.value());
        });
}

void DashboardController::exchangeFetched(std::shared_ptr <Exchange> exchange) {
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getCoinList() {
    
}

void DashboardController::getPriceUpdates(
        QMap <QString, QMap <QString, double> > prices) {
    lastFetchedPrices = prices;
    if(selectedExchange == nullptr)
        return;

    // QMap <QString, double> selectedExchangePrices = prices[selectedExchange->getSymbol()];
    // foreach(const QString& key, selectedExchangePrices.keys())
        // qDebug() << key << " ";
}