#include "controller_candlestick.h"

CandleStickController::CandleStickController(QString objectName) {
    candlestickChart = new CandleStickChart(objectName);
    int week_1 = 259200;
    setTimeLength(week_1);
}

QVBoxLayout* CandleStickController::getView() {
    return candlestickChart;
}

void CandleStickController::notifyOHLCUpdate(
    std::shared_ptr <Pair> pair, QList <OHLC> ohlcData)
{
    candlestickChart->setPair(pair);
    candlestickChart->setOHLCData(ohlcData);
}

void CandleStickController::setPeriod(CandleStickController::PERIOD p) {
    this->period = p;
}

CandleStickController::PERIOD CandleStickController::getPeriod() {
    return period;
}

void CandleStickController::clear() {
    /* staff to clear diagram */
    candlestickChart->clear();
    this->reset();
}

void CandleStickController::reset() {
    this->interval.setEndTime(QDateTime::currentDateTime());
}

void CandleStickController::setStartTime(QDateTime time) {
    this->interval.setStartTime(time);
}

QDateTime CandleStickController::getStartTime() {
    return this->interval.getStartTime();
}

QDateTime CandleStickController::getEndTime() {
    return this->interval.getEndTime();
}

void CandleStickController::setTimeLength(qint64 length) {
    this->interval.setLength(length);
}

qint64 CandleStickController::getTimeLength() {
    return this->interval.getLength();
}
