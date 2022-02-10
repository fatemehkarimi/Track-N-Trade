#ifndef VIEW_CANDLESTICK_H
#define VIEW_CANDLESTICK_H

#include <QList>
#include <memory>
#include <QWidget>
#include <data/ohlc.h>
#include <data/pair.h>

class CandlestickView : public QWidget {
public:
    CandlestickView(QWidget* parent=nullptr)
    : QWidget(parent) {}

    virtual void clear() = 0;
    virtual void setPair(std::shared_ptr <Pair> pair) = 0;
    virtual void setOHLCData(QList <OHLC> ohlcData, QString timeFormat) = 0;
    virtual void awaitLoadingData() = 0;    
};


#endif