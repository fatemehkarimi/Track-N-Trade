#include "proxy_view_candlestick.h"

CandlestickViewProxy::CandlestickViewProxy(QWidget* parent)
    : CandlestickView(parent)
{
    candlestick = new CandleStickChart();
    layout = new QHBoxLayout(this);
    layout->addWidget(candlestick);
}

void CandlestickViewProxy::clear() {

}

void CandlestickViewProxy::setPair(std::shared_ptr <Pair> pair) {
    candlestick->setPair(pair);
}

void CandlestickViewProxy::setOHLCData(QList <OHLC> ohlcData, QString timeFormat) {
    candlestick->setOHLCData(ohlcData, timeFormat);
}