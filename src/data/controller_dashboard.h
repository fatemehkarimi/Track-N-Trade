#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include "exchange.h"
#include "controller.h"
#include <window/main_window.h>

class DashboardController : public QObject,
    public Controller
{
    Q_OBJECT
public:
    explicit DashboardController(Exchange* refExchange);
    void setExchange(QString exchange_name);
    void getCoinList();

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