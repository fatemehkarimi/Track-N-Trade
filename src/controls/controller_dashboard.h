#ifndef CONTROLLER_DASHBOARD_H
#define CONTROLLER_DASHBOARD_H

#include <QtWidgets>
#include <data/exchange.h>

class DashboardController : public QObject
{
public:
    Q_OBJECT
    explicit DashboardController(Exchange* refExchange);

private:
    Exchange* refExchange;
    Exchange* selectedExchange;
};

#endif