#ifndef CHART_CANDLESTICK_H
#define CHART_CANDLESTICK_H

#include <QCandlestickSeries>
#include <QVBoxLayout>

class CandleStickChart : public QVBoxLayout
{
public:
    explicit CandleStickChart(QString objectName);

private:
};

#endif