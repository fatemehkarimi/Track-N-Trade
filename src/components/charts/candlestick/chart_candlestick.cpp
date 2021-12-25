#include "chart_candlestick.h"

CandleStickChart::CandleStickChart(QString objectName) {
    chart = new QtCharts::QChart();
    view = new QtCharts::QChartView(chart);
    this->addWidget(view);
}