#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include <window/main_window.h>
#include <components/table_market/table_market.h>
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
    void setExchange(QString exchangeSymbol);
    void getAssetList();
    void setPricesToTable();
    void setPriceChangesToTable();

private slots:
    void exchangeFetched(std::shared_ptr <Exchange> exchange);
    void getPriceUpdates(QMap <QString, Price> prices) override;
    void getPriceChangesUpdates(QMap <QString, Price> prices) override;

signals:
    void selectedExchangeChanged();

private:
    std::shared_ptr <Exchange> selectedExchange;
    APIManager* refAPI;
    MainWindow* view;
    MarketTable* marketTable;
};

#endif