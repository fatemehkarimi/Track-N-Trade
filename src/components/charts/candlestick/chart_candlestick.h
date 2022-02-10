#ifndef CHART_CANDLESTICK_H
#define CHART_CANDLESTICK_H

#include <memory>
#include <QtGlobal>
#include <QHBoxLayout>
#include <QLineSeries>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QChart>
#include <QChartView>
#include <data/pair.h>
#include <data/ohlc.h>
#include "view_candlestick.h"

class CandleStickChart : public CandlestickView
{
public:
    explicit CandleStickChart();
    void clear() override;
    void setPair(std::shared_ptr <Pair> pair) override;
    void setOHLCData(QList <OHLC> ohlcData, QString timeFormat) override;

private:
    void setupCandlestickSeries();
    void setupTimeSeries();
    void setupTimeAxis(QString timeFormat);
    void setupCandleAxis();
    void clearAxes();
    void clearTimeAxis();
    void clearCandleAxis();
    void setCandleAxisBoundries();

    std::shared_ptr <Pair> pair;

    QtCharts::QChart* chart = nullptr;
    QtCharts::QCandlestickSeries* candlestickSeries = nullptr;
    QtCharts::QChartView* view = nullptr;
    QtCharts::QLineSeries* timeSeries = nullptr;

    QtCharts::QDateTimeAxis* timeAxis = nullptr;
    QtCharts::QValueAxis* candleAxis = nullptr;
};

#endif