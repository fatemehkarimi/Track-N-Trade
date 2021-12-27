#include "controller_candlestick.h"

CandleStickController::CandleStickController(QString objectName) {
    candlestickChart = new CandleStickChart(objectName);
}

QVBoxLayout* CandleStickController::getView() {
    return candlestickChart;
}

void CandleStickController::notifyOHLCUpdate(
    std::shared_ptr <Pair> pair, QList <OHLC> ohlcData)
{
    qDebug() << "received data = " << ohlcData.size();
}