#include "controller_candlestick.h"

CandleStickController::CandleStickController(QString objectName) {
    candlestickChart = new CandleStickChart(objectName);
}

QVBoxLayout* CandleStickController::getView() {
    return candlestickChart;
}