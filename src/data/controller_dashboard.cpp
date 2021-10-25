#include "controller_dashboard.h"
#include <settings/settings_window.h>

DashboardController::DashboardController(APIManager* refAPI)
    :refAPI(refAPI)
{
    refAPI->registerPriceObserver(this);

    Settings::Window* windowSettings = new Settings::Window(0.8, 0.8);
    view = new MainWindow(windowSettings, this, refAPI);
    marketTable = view->getMarketTable();

    view->show();
}

void DashboardController::setExchange(QString exchangeSymbol) {
    selectedExchange = refAPI->getExchangeBySymbol(exchangeSymbol);
    selectedExchange->getPairList();

    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(selectedExchange.get(),
            &Exchange::pairListReady, this, [=](Container <Pair> pairList){
            QObject::disconnect(*conn);

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
        marketTable->updatePairPrice(*prices.find(key));
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
        marketTable->updatePairPriceChange(*prices.find(key));
}