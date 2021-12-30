#include "chart_candlestick.h"
#include "settings/settings_app.h"
#include "settings/settings_chart.h"

using namespace QtCharts;

CandleStickChart::CandleStickChart(QString objectName) {
    chart = new QtCharts::QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitleFont(
        Settings::App::getInstance()->
            getChartSettings().getChartTitleFont());

    view = new QtCharts::QChartView(chart);
    this->addWidget(view);
}

void CandleStickChart::setupCandlestick() {
    candlestick = new QtCharts::QCandlestickSeries();
    Settings::Chart chartSettings = 
        Settings::App::getInstance()->getChartSettings();

    candlestick->setIncreasingColor(chartSettings.getIncreasingColor());
    candlestick->setDecreasingColor(chartSettings.getDecreasingColor());
}

void CandleStickChart::setPair(std::shared_ptr <Pair> pair) {
    this->pair = pair;
}

void CandleStickChart::setOHLCData(QList <OHLC> ohlcData) {
    this->clearCandlestick();
    setupCandlestick();

    QStringList categories;
    foreach(OHLC ohlc, ohlcData) {
        qreal timestamp = ohlc.getCloseTime().toMSecsSinceEpoch();
        qreal open = ohlc.getOpenPrice().getLatestPrice();
        qreal high = ohlc.getHighPrice().getLatestPrice();
        qreal low = ohlc.getLowPrice().getLatestPrice();
        qreal close = ohlc.getClosePrice().getLatestPrice();
        QtCharts::QCandlestickSet *set = 
            new QtCharts::QCandlestickSet(open, high, low, close, timestamp);
        
        if(set) {
            candlestick->append(set);
            categories << ohlc.getCloseTime().toString("h:m ap d MMM");
        }
    }
    chart->addSeries(candlestick);
    this->createAxes(categories);
    chart->setTitle(pair->getBase()->getName());

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void CandleStickChart::clearCandlestick() {
    if(candlestick == nullptr)
        return;

    chart->removeSeries(candlestick);
    candlestick->clear();
    delete candlestick;
    candlestick = nullptr;
}

void CandleStickChart::createAxes(QStringList categories) {
    chart->createDefaultAxes();
    this->setupXAxis(categories);
    this->setupYAxis();
}

void CandleStickChart::setupXAxis(QStringList categories) {
    QBarCategoryAxis *axisX = 
        qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);
}

void CandleStickChart::setupYAxis() {
    QValueAxis *axisY = 
        qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);
}

void CandleStickChart::clearAxes() {
    QBarCategoryAxis *axisX = 
        qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    if(axisX == nullptr)
        return;

    chart->removeAxis(axisX);

    QValueAxis *axisY = 
        qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    if(axisY == nullptr)
        return;
    chart->removeAxis(axisY);
}

void CandleStickChart::clear() {
    this->clearAxes();
    this->clearCandlestick();
    chart->setTitle("");
}