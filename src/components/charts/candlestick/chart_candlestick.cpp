#include "chart_candlestick.h"
#include "settings/settings_app.h"
#include "settings/settings_chart.h"

CandleStickChart::CandleStickChart(QString objectName) {
    setupCandleStick();
    chart = new QtCharts::QChart();
    chart->addSeries(candlestick);

    view = new QtCharts::QChartView(chart);
    this->addWidget(view);
}

void CandleStickChart::setupCandleStick() {
    candlestick = new QtCharts::QCandlestickSeries();
    Settings::Chart chartSettings = 
        Settings::App::getInstance()->getChartSettings();

    candlestick->setIncreasingColor(chartSettings.getIncreasingColor());
    candlestick->setDecreasingColor(chartSettings.getDecreasingColor());
}