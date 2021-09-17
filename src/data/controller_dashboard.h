#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include <window/main_window.h>
#include "exchange.h"
#include "controller.h"
#include "observer_price.h"

class DashboardController : public QObject,
    public Controller,
    public PriceObserver
{
    Q_OBJECT
public:
    explicit DashboardController(Exchange* refExchange);
    void setExchange(QString exchange_name);
    void getCoinList();
    void getPriceUpdates(QMap <QString, QMap <QString, double> > prices) override;

private slots:
    void exchangeFetched(Exchange* exchange);

signals:
    void selectedExchangeChanged();

private:
    Exchange* selectedExchange;
    Exchange* refExchange;
    MainWindow* view;
};

#endif