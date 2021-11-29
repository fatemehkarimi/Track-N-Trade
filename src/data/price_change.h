#ifndef PRICE_CHANGE_H
#define PRICE_CHANGE_H

#include <QtWidgets>
#include <QMetaType>
#include <QString>

class PriceChange {
public:
    PriceChange()
    {}

    PriceChange(QString exchange, QString pair, double percentage);
    PriceChange(const PriceChange& change);

    enum CHANGE_STATUS {
        POSITIVE,
        ZERO,
        NEGATIVE
    };

    bool isEmpty();
    void update(double percentage);
    double getChangePercentage();
    QString getExchangeSymbol();
    QString getPairSymbol();
    CHANGE_STATUS getStatus();

private:
    void updateStatus();

    QString exchange;   // symbol of exchange
    QString pair;       // symbol of pair
    double percentage;
    CHANGE_STATUS changeStatus = CHANGE_STATUS::ZERO;
};

Q_DECLARE_METATYPE(PriceChange)
#endif