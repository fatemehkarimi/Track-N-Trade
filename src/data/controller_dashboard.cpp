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
    if(selectedExchange != nullptr) {
        selectedExchange->deactivateAllPairTracking();
        this->neglectSinglePair();
    }

    selectedExchange = refAPI->getExchangeBySymbol(exchangeSymbol);
    selectedExchange->getPairList();
    selectedExchange->activateAllPairTracking();
    selectedExchange->registerPriceObserver(this);
    selectedExchange->registerSinglePairPriceObserver(view->getPriceTable());

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
    QMap <QString, PriceChange> priceChanges = selectedExchange->getPriceChanges();
    foreach(const QString& key, priceChanges.keys())
        marketTable->updatePairPriceChange(*priceChanges.find(key));
}

void DashboardController::handlePairSelected(QString pairSymbol) {
    this->trackSinglePair(pairSymbol);
}

void DashboardController::trackSinglePair(QString pairSymbol) {
    if(selectedExchange == nullptr)
        return;

    this->neglectSinglePair();
    std::shared_ptr <Pair> pair = selectedExchange->getPair(pairSymbol);

    if(pair != nullptr) {
        selectedExchange->activateOHLCTracker(pair);
        selectedExchange->registerOHLCObserver(view->getCandleStickController());
        this->getOHLCDataAsync(
            view->getCandleStickController()->getPeriod(),
            view->getCandleStickController()->getStartTime(),
            view->getCandleStickController()->getEndTime());

        selectedExchange->activateLatestPriceTracker(pair);
        selectedExchange->activateLowestPriceTracker(pair);
        selectedExchange->activateHighestPriceTracker(pair);
        selectedExchange->activatePriceChangeTracker(pair);
    }
}

void DashboardController::neglectSinglePair() {
    if(selectedExchange == nullptr)
        return;

    selectedExchange->deactivateOHLCTracker();
    selectedExchange->deactivateLatestPriceTracker();
    selectedExchange->deactivateLowestPriceTracker();
    selectedExchange->deactivateHighestPriceTracker();
    selectedExchange->deactivatePriceChangeTracker();
}

void DashboardController::getOHLCDataAsync(
    int period, QDateTime after, QDateTime before)
{
    if(selectedExchange == nullptr)
        return;
    selectedExchange->getOHLCAsync(period, after, before);
}

void DashboardController::handleOHLCDataRequest(
    int period, QDateTime after, QDateTime before)
{
    getOHLCDataAsync(period, after, before);
}