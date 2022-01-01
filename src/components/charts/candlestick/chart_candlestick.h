#ifndef CHART_CANDLESTICK_H
#define CHART_CANDLESTICK_H

#include <memory>
#include <QtGlobal>
#include <QVBoxLayout>
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
#include "chart_control.h"

class CandleStickChart : public QVBoxLayout
{
public:
    explicit CandleStickChart(QString objectName);
    void setPair(std::shared_ptr <Pair> pair);
    void setOHLCData(QList <OHLC> ohlcData);
    void clear();

private:
    void setupCandlestickSeries();
    void setupTimeSeries();
    void setupTimeAxis();
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

    ChartControl* chartControl = nullptr;
};

#endif