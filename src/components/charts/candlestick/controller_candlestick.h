#ifndef CONTROLLER_CANDLESTICK_H
#define CONTROLLER_CANDLESTICK_H

#include <QtWidgets>
#include <data/observer_ohlc.h>
#include <utils/time_interval.h>
#include "chart_candlestick.h"

class CandleStickController : public OHLCObserver {
public:
    enum PERIOD {
        M_1 = 60,
        M_3 = 180,
        M_5 = 300,
        M_15 = 900,
        M_30 = 1800,
        H_1 = 3600,
        H_2 = 7200,
        H_4 = 14400,
        H_6 = 21600,
        H_12 = 43200,
        D_1 = 86400,
        D_3 = 259200,
        W_1 = 604800
    };

    explicit CandleStickController(QString objectName);
    void notifyOHLCUpdate(
        std::shared_ptr <Pair> pair, QList <OHLC> ohlcData) override;

    QVBoxLayout* getView();
    void clear();
    void reset();

    void setPeriod(PERIOD);
    PERIOD getPeriod();

    void setStartTime(QDateTime time);
    QDateTime getStartTime();
    QDateTime getEndTime();

    void setTimeLength(qint64 length);
    qint64 getTimeLength();

private:
    CandleStickChart* candlestickChart = nullptr;
    PERIOD period = PERIOD::H_6;
    TimeInterval interval;
};

#endif