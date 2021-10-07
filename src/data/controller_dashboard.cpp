#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(Exchange* refExchange) {
    this->refExchange = refExchange;
    refExchange->registerPriceObserver(this);

    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refExchange);
    coin_table = view->getMarketTable();

    view->show();
}

void DashboardController::setExchange(QString exchange_name) {
    selectedExchange = refExchange->getExchange(exchange_name);
    selectedExchange->getAssetList();

    //TODO: do not use signals and slots. use QEvent loop or other thing
    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(selectedExchange.get(),
            &Exchange::assetListReady, this, [=](QMap <QString, std::shared_ptr <Asset> > list){
            QObject::disconnect(*conn);

            coin_table->clear();
            for(auto itm = list.begin(); itm != list.end(); ++itm)
                coin_table->addCoin(itm.value());

            setPricesToTable();
            setPriceChangesToTable();
            emit coin_table->coinListUpdated();
        });
}

void DashboardController::exchangeFetched(std::shared_ptr <Exchange> exchange) {
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getAssetList() {
    
}

void DashboardController::getPriceUpdates(
        QMap <QString, QMap <QString, Price> > prices) {
    lastFetchedPrices = prices;
    if(selectedExchange == nullptr)
        return;
    this->setPricesToTable();
}

void DashboardController::setPricesToTable() {
    QMap <QString, Price> prices = lastFetchedPrices[selectedExchange->getSymbol()];

    foreach(const QString& key, prices.keys())
        coin_table->updateCoinPrice(key, *prices.find(key));
}

void DashboardController::getPriceChangesUpdates(
        QMap <QString, QMap <QString, Price> > prices) {
    lastFetchedPrices = prices;
    if(selectedExchange == nullptr)
        return;
    this->setPriceChangesToTable();
}

void DashboardController::setPriceChangesToTable() {
    QMap <QString, Price> prices = lastFetchedPrices[selectedExchange->getSymbol()];
    foreach(const QString& key, prices.keys())
        coin_table->updatePriceChange(key, *prices.find(key));
}