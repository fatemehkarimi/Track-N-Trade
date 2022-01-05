#include "chart_candlestick.h"
#include "settings/settings_app.h"
#include "settings/settings_chart.h"

CandleStickChart::CandleStickChart() {
    chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->setTitleFont(
        Settings::App::getInstance()->
            getChartSettings().getChartTitleFont());

    view = new QtCharts::QChartView(chart);
}

QtCharts::QChartView* CandleStickChart::getView() {
    return view;
}

void CandleStickChart::setPair(std::shared_ptr <Pair> pair) {
    this->pair = pair;
}

void CandleStickChart::setupCandlestickSeries() {
    candlestickSeries = new QtCharts::QCandlestickSeries();
    Settings::Chart chartSettings = 
        Settings::App::getInstance()->getChartSettings();

    candlestickSeries->setIncreasingColor(chartSettings.getIncreasingColor());
    candlestickSeries->setDecreasingColor(chartSettings.getDecreasingColor());
}

void CandleStickChart::setupTimeSeries() {
    timeSeries = new QtCharts::QLineSeries();
}

void CandleStickChart::setupTimeAxis() {
    timeAxis = new QtCharts::QDateTimeAxis();
    timeAxis->setFormat("MMM dd");
    timeAxis->setGridLineVisible(false);
}

void CandleStickChart::setupCandleAxis() {
    candleAxis = new QtCharts::QValueAxis();
}

void CandleStickChart::setCandleAxisBoundries() {
    candleAxis->setMin(candleAxis->min() * 0.98);
    candleAxis->setMax(candleAxis->max() * 1.02);
}


void CandleStickChart::setOHLCData(QList <OHLC> ohlcData) {
    chart->removeAllSeries();
    clearAxes();
    setupCandlestickSeries();
    setupTimeSeries();

    setupTimeAxis();
    setupCandleAxis();
    chart->addAxis(timeAxis, Qt::AlignBottom);
    chart->addAxis(candleAxis, Qt::AlignLeft);

    foreach(OHLC ohlc, ohlcData) {
        qreal timestamp = ohlc.getCloseTime().toMSecsSinceEpoch();
        qreal open = ohlc.getOpenPrice().getLatestPrice();
        qreal high = ohlc.getHighPrice().getLatestPrice();
        qreal low = ohlc.getLowPrice().getLatestPrice();
        qreal close = ohlc.getClosePrice().getLatestPrice();
        QtCharts::QCandlestickSet *set = 
            new QtCharts::QCandlestickSet(open, high, low, close, timestamp);
        
        if(set) {
            candlestickSeries->append(set);
            *timeSeries << QPointF(timestamp, 0);
        }
    }

    chart->addSeries(candlestickSeries);
    chart->addSeries(timeSeries);

    candlestickSeries->attachAxis(candleAxis);
    candlestickSeries->attachAxis(timeAxis);
    timeSeries->attachAxis(timeAxis);

    setCandleAxisBoundries();

    chart->setTitle(pair->getBase()->getName());
}

void CandleStickChart::clearAxes() {
    clearTimeAxis();
    clearCandleAxis();
}

void CandleStickChart::clearTimeAxis() {
    if(timeAxis != nullptr) {
        chart->removeAxis(timeAxis);
        delete timeAxis;
        timeAxis = nullptr;
    }
}

void CandleStickChart::clearCandleAxis() {
    if(candleAxis != nullptr) {
        chart->removeAxis(candleAxis);
        delete candleAxis;
        candleAxis = nullptr;
    }
}

void CandleStickChart::clear() {
    chart->removeAllSeries();
    clearAxes();
    chart->setTitle("");
}