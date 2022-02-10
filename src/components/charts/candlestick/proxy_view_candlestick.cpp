#include "proxy_view_candlestick.h"

CandlestickViewProxy::CandlestickViewProxy(QWidget* parent)
    : CandlestickView(parent)
{
    candlestick = new CandleStickChart();
    layout = new QGridLayout(this);
    layout->addWidget(candlestick, 0, 0, -1, -1);
}

void CandlestickViewProxy::setupLoadingObject() {
    if(loadingThrobber == nullptr) {
        loadingThrobber = new Throbber();
        layout->addWidget(loadingThrobber, 0, 0, -1, -1);
    }
}

void CandlestickViewProxy::removeLoadingObject() {
    if(loadingThrobber != nullptr) {
        layout->removeWidget(loadingThrobber);
        delete loadingThrobber;
        loadingThrobber = nullptr;
    }
}

void CandlestickViewProxy::clear() {
    candlestick->clear();
    removeLoadingObject();
}

void CandlestickViewProxy::setPair(std::shared_ptr <Pair> pair) {
    candlestick->setPair(pair);
}

void CandlestickViewProxy::setOHLCData(QList <OHLC> ohlcData, QString timeFormat) {
    candlestick->setOHLCData(ohlcData, timeFormat);
    removeLoadingObject();
}

void CandlestickViewProxy::awaitLoadingData() {
    setupLoadingObject();
}