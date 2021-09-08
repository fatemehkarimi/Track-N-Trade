#ifndef ROUTES_H
#define ROUTES_H

#include <QString>

class Routes {
public:
    virtual QString getBasePath() = 0;
    virtual QString getExchangeListPath() = 0;
    virtual QString getExchangeDetailPath(QString exchange_symbol) = 0;
    virtual QString getExchangeMarketsPath(QString exchange_symbol) = 0;
};
#endif