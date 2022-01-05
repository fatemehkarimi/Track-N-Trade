#include "controller_candlestick.h"

CandleStickController::CandleStickController(QString objectName) {
    candlestickChart = new CandleStickChart();
    chartControl = new ChartControl(this);
    chartControl->setEnabled(false);

    buildView();
    int day_4 = 345600;
    setTimeLength(day_4);
}

void CandleStickController::buildView() {
    viewLayout = new QVBoxLayout();
    viewLayout->addWidget(candlestickChart->getView());
    viewLayout->addWidget(chartControl);
}

QVBoxLayout* CandleStickController::getView() {
    return viewLayout;
}

void CandleStickController::notifyOHLCUpdate(
    std::shared_ptr <Pair> pair, QList <OHLC> ohlcData)
{
    chartControl->setEnabled(true);
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
    chartControl->setEnabled(false);
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
