#include "chart_candlestick.h"
#include "settings/settings_app.h"
#include "settings/settings_chart.h"

using namespace QtCharts;

CandleStickChart::CandleStickChart(QString objectName) {
    chart = new QtCharts::QChart();

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
            categories << ohlc.getCloseTime().toString("d MMM");
        }
    }
    chart->addSeries(candlestick);
    chart->setTitle(pair->getBase()->getName());
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

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