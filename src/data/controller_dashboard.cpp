#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(APIManager* refAPI)
    :refAPI(refAPI)
{
    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refAPI);
    view->show();
}

void DashboardController::setExchange(QString exchangeSymbol) {
    if(selectedExchange != nullptr)
        selectedExchange->deactivatePriceTracker();

    selectedExchange = refAPI->getExchangeBySymbol(exchangeSymbol);
    selectedExchange->getPairList();
    selectedExchange->activatePriceTracker();
    selectedExchange->registerPriceObserver(this);

    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(selectedExchange.get(),
            &Exchange::pairListReady, this, [=](Container <Pair> pairList){
            QObject::disconnect(*conn);

            MarketTable* marketTable = view->getMarketTable();
            marketTable->clear();
            auto iterator = pairList.createIterator();
            while(iterator.hasNext()) {
                std::shared_ptr <Pair> pair = iterator.next();
                marketTable->addPair(pair);
            }

            setPricesToTable();
            setPriceChangesToTable();
            //TODO: it is better that marketTable itself emits this signal
            emit marketTable->assetListUpdated();
        });
}

void DashboardController::exchangeFetched(std::shared_ptr <Exchange> exchange) {
    selectedExchange = exchange;
    emit selectedExchangeChanged();
}

void DashboardController::getAssetList() {
    
}

void DashboardController::notifyPriceUpdates() {
    this->setPricesToTable();
}

void DashboardController::setPricesToTable() {
    if(selectedExchange == nullptr)
        return;
    MarketTable* marketTable = view->getMarketTable();
    QMap <QString, Price> prices = selectedExchange->getPrices();
    foreach(const QString& key, prices.keys())
        marketTable->updatePairPrice(*prices.find(key));
}

void DashboardController::notifyPriceChangeUpdates() {
    this->setPriceChangesToTable();
}

void DashboardController::setPriceChangesToTable() {
    if(selectedExchange == nullptr)
        return;
    MarketTable* marketTable = view->getMarketTable();
    QMap <QString, Price> prices = selectedExchange->getPrices();
    foreach(const QString& key, prices.keys())
        marketTable->updatePairPriceChange(*prices.find(key));
}