#ifndef CHART_CANDLESTICK_H
#define CHART_CANDLESTICK_H

#include <QVBoxLayout>
#include <QCandlestickSeries>
#include <QChart>
#include <QChartView>

class CandleStickChart : public QVBoxLayout
{
public:
    explicit CandleStickChart(QString objectName);

private:
    void setupCandleStick();

    QtCharts::QChart* chart = nullptr;
    QtCharts::QCandlestickSeries* candlestick = nullptr;
    QtCharts::QChartView* view = nullptr;
};

#endif