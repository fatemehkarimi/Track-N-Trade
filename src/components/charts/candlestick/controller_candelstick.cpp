#include "controller_candlestick.h"

CandleStickController::CandleStickController(Controller* controller)
    : controller(controller)
{
    candlestickChart = new CandleStickChart();
    intervalController = new IntervalControl(this);
    intervalController->setEnabled(false);

    buildView();
    int day_4 = 345600;
    setTimeLength(day_4);
}

void CandleStickController::buildView() {
    viewLayout = new QVBoxLayout();
    viewLayout->addWidget(candlestickChart->getView());
    viewLayout->addWidget(intervalController);
}

QVBoxLayout* CandleStickController::getView() {
    return viewLayout;
}

void CandleStickController::notifyOHLCUpdate(
    std::shared_ptr <Pair> pair, QList <OHLC> ohlcData)
{
    intervalController->setEnabled(true);
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
    intervalController->setEnabled(false);
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
    controller->handleOHLCDataRequest(
        period, interval.getStartTime(), interval.getEndTime());
}

qint64 CandleStickController::getTimeLength() {
    return this->interval.getLength();
}
