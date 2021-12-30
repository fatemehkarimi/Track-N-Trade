#ifndef CHART_CANDLESTICK_H
#define CHART_CANDLESTICK_H

#include <memory>
#include <QtGlobal>
#include <QVBoxLayout>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <data/pair.h>
#include <data/ohlc.h>

class CandleStickChart : public QVBoxLayout
{
public:
    explicit CandleStickChart(QString objectName);
    void setPair(std::shared_ptr <Pair> pair);
    void setOHLCData(QList <OHLC> ohlcData);
    void clear();

private:
    void setupCandlestick();
    void clearCandlestick();
    void createAxes(QStringList categories);
    void setupXAxis(QStringList categories);
    void setupYAxis();
    void clearAxes();

    QtCharts::QChart* chart = nullptr;
    QtCharts::QCandlestickSeries* candlestick = nullptr;
    QtCharts::QChartView* view = nullptr;

    std::shared_ptr <Pair> pair;
};

#endif