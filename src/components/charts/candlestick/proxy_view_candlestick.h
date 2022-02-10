#ifndef PROXY_VIEW_CANDLESTICK_H
#define PROXY_VIEW_CANDLESTICK_H

#include <QList>
#include <memory>
#include <QGridLayout>
#include <data/ohlc.h>
#include <data/pair.h>
#include <components/throbber/throbber.h>
#include "view_candlestick.h"
#include "chart_candlestick.h"


class CandlestickViewProxy : public CandlestickView {
public:
    explicit CandlestickViewProxy(QWidget* parent=nullptr);
    void clear() override;
    void setPair(std::shared_ptr <Pair> pair) override;
    void setOHLCData(QList <OHLC> ohlcData, QString timeFormat) override;
    void awaitLoadingData() override;

private:
    void setupLoadingObject();
    void removeLoadingObject();

    CandlestickView* candlestick = nullptr;
    QGridLayout* layout = nullptr;
    Throbber* loadingThrobber = nullptr;
};


#endif