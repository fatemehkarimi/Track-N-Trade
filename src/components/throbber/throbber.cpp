#include "throbber.h"

Throbber::Throbber() {    
    series = new QtCharts::QPieSeries();
    series->setHoleSize(0.5);

    view = new QtCharts::QChartView();
    view->setRenderHint(QPainter::Antialiasing);
    view->chart()->legend()->hide();
    view->chart()->addSeries(series);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(view);
    view->chart()->legend()->setBackgroundVisible(false);
    QObject::connect(&timer, &QTimer::timeout, this, &Throbber::handleTimeout);
    timer.start(TIMER_INTERVAL);
}

void Throbber::handleTimeout() {
    timer.start(TIMER_INTERVAL);
    addSlice();
}

void Throbber::addSlice() {
    series->clear();

    for(int i = 0; i < current; ++i) {
        QtCharts::QPieSlice* slice = series->append("", TOTAL_VALUE / (COUNT_SLICES - 1));
        slice->setColor(SHADES[i]);
    }

    QtCharts::QPieSlice* emptySlice = series->append(
        "", TOTAL_VALUE - series->count() * TOTAL_VALUE / (COUNT_SLICES - 1));
    emptySlice->setColor(EMPTY_SHADE);

    current = (current + 1) % COUNT_SLICES;
}