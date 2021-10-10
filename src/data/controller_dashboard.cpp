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

void DashboardController::setExchange(QString exchangeName) {
    selectedExchange = refAPI->getExchange(exchangeName);
    selectedExchange->getAssetList();

    auto conn = std::make_shared <QMetaObject::Connection>();
    *conn = QObject::connect(selectedExchange.get(),
            &Exchange::assetListReady, this, [=](QMap <QString, std::shared_ptr <Asset> > list){
            QObject::disconnect(*conn);

            marketTable->clear();
            for(auto itm = list.begin(); itm != list.end(); ++itm)
                marketTable->addAsset(itm.value());

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
        marketTable->updateAssetPrice(key, *prices.find(key));
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
        marketTable->updatePriceChange(key, *prices.find(key));
}