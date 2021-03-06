#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include <window/main_window.h>
#include <components/tables/table_market/table_market.h>
#include <components/tables/table_price/table_price.h>
#include "controller.h"
#include "observer_price.h"
#include "api_manager.h"
#include "container.h"

class DashboardController : public QObject,
    public Controller,
    public PriceObserver
{
    Q_OBJECT
public:
    explicit DashboardController(APIManager* refAPI);
    void setExchange(QString exchangeSymbol) override;
    void handlePairSelected(QString pairSymbol) override;
    void handleOHLCDataRequest(int period, QDateTime after, QDateTime before) override;

private slots:
    void exchangeFetched(std::shared_ptr <Exchange> exchange);
    void notifyPriceUpdates() override;
    void notifyPriceChangeUpdates() override;
    void trackSinglePair(QString pairSymbol);

signals:
    void selectedExchangeChanged();

private:
    void neglectSinglePair();
    void setPricesToTable();
    void setPriceChangesToTable();
    void getOHLCDataAsync(int period, QDateTime after, QDateTime before);

    std::shared_ptr <Exchange> selectedExchange;
    APIManager* refAPI;
    MainWindow* view;
};

#endif