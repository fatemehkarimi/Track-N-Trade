#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include <window/main_window.h>
#include "exchange.h"
#include "controller.h"
#include "observer_price.h"
#include <components/table_coin.h>

class DashboardController : public QObject,
    public Controller,
    public PriceObserver
{
    Q_OBJECT
public:
    explicit DashboardController(Exchange* refExchange);
    void setExchange(QString exchange_name);
    void getAssetList();
    void setPricesToTable();
    void setPriceChangesToTable();

private slots:
    void exchangeFetched(std::shared_ptr <Exchange> exchange);
    void getPriceUpdates(QMap <QString, QMap <QString, Price> > prices) override;
    void getPriceChangesUpdates(QMap <QString, QMap <QString, Price> > prices) override;

signals:
    void selectedExchangeChanged();

private:
    std::shared_ptr <Exchange> selectedExchange;
    Exchange* refExchange;
    MainWindow* view;
    CoinTable* coin_table;
    QMap <QString, QMap <QString, Price> > lastFetchedPrices;
};

#endif