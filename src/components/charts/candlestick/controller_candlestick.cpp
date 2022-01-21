#include "controller_candlestick.h"

CandleStickController::CandleStickController(Controller* controller)
    : controller(controller)
{
    candlestickChart = new CandleStickChart();
    intervalController = new IntervalController();
    intervalController->setEnabled(false);
    QObject::connect(
        intervalController,
        &IntervalController::intervalChanged,
        this, &CandleStickController::getOHLCDataAsync);

    buildView();
    getOHLCDataAsync();
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
    candlestickChart->setOHLCData(ohlcData, getChartTimeFormat());
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
    intervalController->reset();
}

void CandleStickController::getOHLCDataAsync() {
    setTimeScale();
    controller->handleOHLCDataRequest(
        period,
        intervalController->getStartTime(),
        intervalController->getEndTime());
}

QString CandleStickController::getChartTimeFormat() {
    switch(intervalController->getSelectedInterval()){
        case IntervalController::m_15:
            return "hh:mm";
        case IntervalController::h_1:
            return "hh:mm";
        case IntervalController::h_4:
            return "hh:mm";
        case IntervalController::d_1:
            return "hh:mm";
        case IntervalController::w_1:
            return "MMM d";
        case IntervalController::M_1:
            return "MMM d";
    }
}

void CandleStickController::setTimeScale() {
    switch(intervalController->getSelectedInterval()) {
        case IntervalController::m_15:
            setPeriod(CandleStickController::M_1);
            break;
        case IntervalController::h_1:
            setPeriod(CandleStickController::M_1);
            break;
        case IntervalController::h_4:
            setPeriod(CandleStickController::M_1);
            break;
        case IntervalController::d_1:
            setPeriod(CandleStickController::M_1);
            break;
        case IntervalController::w_1:
            setPeriod(CandleStickController::M_3);
            break;
        case IntervalController::M_1:
            setPeriod(CandleStickController::M_30);
            break;
    }
}