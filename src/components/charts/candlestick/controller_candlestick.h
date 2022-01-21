#ifndef CONTROLLER_CANDLESTICK_H
#define CONTROLLER_CANDLESTICK_H

#include <QtWidgets>
#include <data/controller.h>
#include <data/observer_ohlc.h>
#include "chart_candlestick.h"
#include "interval_controller.h"
#include "chart_common.h"

class CandleStickController : public QObject, public OHLCObserver {
    Q_OBJECT
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

    explicit CandleStickController(Controller* controller);
    void getOHLCDataAsync();
    void notifyOHLCUpdate(
        std::shared_ptr <Pair> pair, QList <OHLC> ohlcData) override;
    

    void buildView();
    QVBoxLayout* getView();

    void clear();
    void reset();

    void setPeriod(PERIOD);
    PERIOD getPeriod();

    friend class CandleStickChart;

protected:
    QString getChartTimeFormat();
    void setTimeScale();

private:
    QVBoxLayout* viewLayout = nullptr;
    IntervalController* intervalController = nullptr;
    CandleStickChart* candlestickChart = nullptr;
    Controller* controller = nullptr;
    PERIOD period = PERIOD::H_1;
};

#endif