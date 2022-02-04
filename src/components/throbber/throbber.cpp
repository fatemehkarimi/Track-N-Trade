#include "throbber.h"

Throbber::Throbber(QWidget* parent)
    : QWidget(parent)
{
    series = new QtCharts::QPieSeries();
    series->setHoleSize(0.5);

    setupView();
    view->chart()->addSeries(series);
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

    QColor white = QColor(255, 255, 255);
    white.setAlphaF(0.5);
    view->chart()->setBackgroundBrush(QBrush(white));
}

Throbber::~Throbber() {
    delete series;
    delete view;
    series = nullptr;
    view = nullptr;
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