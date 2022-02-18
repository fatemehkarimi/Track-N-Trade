#include "throbber.h"

Throbber::Throbber(QWidget* parent)
    : QWidget(parent)
{
    registerAsMetaType();
    setupSeriesHandler();

    setupView();
    setStyleSheet("background-color: rgba(0, 0, 0, 0)");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(view);
    
    QObject::connect(&timer, &QTimer::timeout, this, &Throbber::handleTimeout);
    timer.start(TIMER_INTERVAL);
}

void Throbber::setupView() {
    view = new QtCharts::QChartView();
    view->setRenderHint(QPainter::Antialiasing);

    view->chart()->legend()->hide();
    view->chart()->setBackgroundRoundness(0);
    view->chart()->layout()->setContentsMargins(0, 0, 0, 0);

    QColor white = QColor(255, 255, 255);
    white.setAlphaF(0.5);
    view->chart()->setBackgroundBrush(QBrush(white));
}

void Throbber::setupSeriesHandler() {
    seriesHandler = new SeriesHandler();
    seriesHandler->moveToThread(&seriesHandlerThread);
    QObject::connect(
        this,
        &Throbber::updateSeries,
        seriesHandler,
        &SeriesHandler::handle);

    QObject::connect(
        seriesHandler,
        &SeriesHandler::seriesReady,
        this,
        &Throbber::handleSeriesUpdate);
    
    seriesHandlerThread.start();
}

Throbber::~Throbber() {
    seriesHandlerThread.quit();
    seriesHandlerThread.wait();

    delete view;
    view = nullptr;

    delete seriesHandler;
    seriesHandler = nullptr;
}

void Throbber::handleTimeout() {
    emit updateSeries(current);
    current = (current + 1) % COUNT_SLICES;
    timer.start(TIMER_INTERVAL);
}

void Throbber::handleSeriesUpdate(QtCharts::QPieSeries* series) {
    if(!view->chart()->series().isEmpty())
        view->chart()->removeAllSeries();

    view->chart()->addSeries(series);
}

void Throbber::registerAsMetaType() {
    static bool registered = false;
    if(!registered) {
        registered = true;
        qRegisterMetaType <QtCharts::QPieSeries*>("QtCharts::QPieSeries*");
    }
}