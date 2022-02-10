#include "controller_candlestick.h"

CandleStickController::CandleStickController(Controller* controller)
    : controller(controller)
{
    candlestickView = new CandlestickViewProxy();
    intervalController = new IntervalController();
    intervalController->setEnabled(false);
    QObject::connect(
        intervalController,
        &IntervalController::intervalChanged,
        this, &CandleStickController::getOHLCDataAsync);

    buildView();
    // getOHLCDataAsync();
}

void CandleStickController::buildView() {
    viewLayout = new QVBoxLayout();    
    viewLayout->addWidget(candlestickView);
    viewLayout->addWidget(intervalController);
}

QLayout* CandleStickController::getView() {
    return viewLayout;
}

void CandleStickController::notifyOHLCUpdate(
    std::shared_ptr <Pair> pair, QList <OHLC> ohlcData)
{
    intervalController->setEnabled(true);
    candlestickView->setPair(pair);
    candlestickView->setOHLCData(ohlcData, getChartTimeFormat());
}

void CandleStickController::setPeriod(CandleStickController::PERIOD p) {
    this->period = p;
}

CandleStickController::PERIOD CandleStickController::getPeriod() {
    return period;
}

void CandleStickController::clear() {
    intervalController->setEnabled(false);
    candlestickView->clear();
    this->reset();
}

void CandleStickController::reset() {
    intervalController->reset();
}

void CandleStickController::getOHLCDataAsync() {
    candlestickView->awaitLoadingData();
    intervalController->setEnabled(false);

    setTimeScale();
    controller->handleOHLCDataRequest(
        period,
        intervalController->getStartTime(),
        intervalController->getEndTime());
}

QString CandleStickController::getChartTimeFormat() {
    switch(intervalController->getSelectedInterval()){
        case candlestick::INTERVAL::m_15:
            return "hh:mm";
        case candlestick::INTERVAL::h_1:
            return "hh:mm";
        case candlestick::INTERVAL::h_4:
            return "hh:mm";
        case candlestick::INTERVAL::d_1:
            return "MMM d hh:mm";
        case candlestick::INTERVAL::w_1:
            return "MMM d";
        case candlestick::INTERVAL::M_1:
            return "MMM d";
    }
}

void CandleStickController::setTimeScale() {
    switch(intervalController->getSelectedInterval()) {
        case candlestick::INTERVAL::m_15:
            setPeriod(CandleStickController::M_1);
            break;
        case candlestick::INTERVAL::h_1:
            setPeriod(CandleStickController::M_1);
            break;
        case candlestick::INTERVAL::h_4:
            setPeriod(CandleStickController::M_3);
            break;
        case candlestick::INTERVAL::d_1:
            setPeriod(CandleStickController::M_15);
            break;
        case candlestick::INTERVAL::w_1:
            setPeriod(CandleStickController::H_2);
            break;
        case candlestick::INTERVAL::M_1:
            setPeriod(CandleStickController::H_6);
            break;
    }
}