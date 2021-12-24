#ifndef CONTROLLER_CANDLESTICK_H
#define CONTROLLER_CANDLESTICK_H

#include <QtWidgets>
#include "chart_candlestick.h"

class CandleStickController {
public:
    explicit CandleStickController(QString objectName);
    QVBoxLayout* getView();

private:
    CandleStickChart* candlestickChart = nullptr;
};

#endif