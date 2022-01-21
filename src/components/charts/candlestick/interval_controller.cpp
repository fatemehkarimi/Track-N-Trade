#include "interval_controller.h"

IntervalController::IntervalController() {
    layout = new QHBoxLayout(this);

    setupLabel();
    layout->addWidget(label);

    ibM15 = new IntervalButton(getIntervalValue(IntervalController::m_15), "15m");
    ibH1 = new IntervalButton(getIntervalValue(IntervalController::h_1), "1h");
    ibH4 = new IntervalButton(getIntervalValue(IntervalController::h_4), "4h");
    ibD1 = new IntervalButton(getIntervalValue(IntervalController::d_1), "1d");
    ibW1 = new IntervalButton(getIntervalValue(IntervalController::w_1), "1w");
    ibMon1 = new IntervalButton(getIntervalValue(IntervalController::M_1), "1M");

    QObject::connect(
        ibM15, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);
    
    QObject::connect(
        ibH1, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);

    QObject::connect(
        ibH4, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);

    QObject::connect(
        ibD1, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);

    QObject::connect(
        ibW1, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);

    QObject::connect(
        ibMon1, &IntervalButton::notifyInterval,
        this, &IntervalController::handleIntervalChange);

    layout->addWidget(ibM15);
    layout->addWidget(ibH1);
    layout->addWidget(ibH4);
    layout->addWidget(ibD1);
    layout->addWidget(ibW1);
    layout->addWidget(ibMon1);
    layout->addStretch(1);

    reset();
}

void IntervalController::setupLabel() {
    label = new QLabel("Time");
    label->setObjectName("chartTimeLabel");
    label->setFont(
        Settings::App::getInstance()->
            getChartSettings().getChartLabelFont());
    label->setAlignment(Qt::AlignLeft);
}

void IntervalController::handleIntervalChange(qint64 iSecs) {
    emit intervalChanged();
}

qint64 IntervalController::getIntervalValue(IntervalController::INTERVAL i) {
    switch(i){
        case IntervalController::INTERVAL::m_15:
            return 900;
        case IntervalController::INTERVAL::h_1:
            return 3600;
        case IntervalController::INTERVAL::h_4:
            return 14400;
        case IntervalController::INTERVAL::d_1:
            return 86400;
        case IntervalController::INTERVAL::w_1:
            return 604800;
        case IntervalController::INTERVAL::M_1:
            return 2592000;
    }
}

IntervalController::INTERVAL IntervalController::getSelectedInterval() {
    return selectedInterval;
}

void IntervalController::reset() {
    selectedInterval = INTERVAL::d_1;
    interval = TimeInterval(
        QDateTime::currentDateTime(),
        getIntervalValue(selectedInterval));
    interval.moveIntervalBackward();
}

QDateTime IntervalController::getStartTime() {
    return interval.getStartTime();
}

QDateTime IntervalController::getEndTime() {
    return interval.getEndTime();
}