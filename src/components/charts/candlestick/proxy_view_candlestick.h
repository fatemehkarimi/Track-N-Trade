#ifndef PROXY_VIEW_CANDLESTICK_H
#define PROXY_VIEW_CANDLESTICK_H

#include <QList>
#include <memory>
#include <QHBoxLayout>
#include <data/ohlc.h>
#include <data/pair.h>
#include "view_candlestick.h"
#include "chart_candlestick.h"


class CandlestickViewProxy : public CandlestickView {
public:
    explicit CandlestickViewProxy(QWidget* parent=nullptr);
    void clear() override;
    void setPair(std::shared_ptr <Pair> pair) override;
    void setOHLCData(QList <OHLC> ohlcData, QString timeFormat) override;

private:
    CandlestickView* candlestick = nullptr;
    QHBoxLayout* layout = nullptr;
};


#endif