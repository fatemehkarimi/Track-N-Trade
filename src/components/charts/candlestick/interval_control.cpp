#include "interval_control.h"

IntervalControl::IntervalControl(CandleStickController* controller) {
    this->controller = controller;
    layout = new QHBoxLayout(this);

    setupLabel();
    layout->addWidget(label);

    ibM15 = new IntervalButton(getIntervalValue(IntervalControl::m_15), "15m");
    ibH1 = new IntervalButton(getIntervalValue(IntervalControl::h_1), "1h");
    ibH4 = new IntervalButton(getIntervalValue(IntervalControl::h_4), "4h");
    ibD1 = new IntervalButton(getIntervalValue(IntervalControl::d_1), "1d");
    ibW1 = new IntervalButton(getIntervalValue(IntervalControl::w_1), "1w");
    ibMon1 = new IntervalButton(getIntervalValue(IntervalControl::M_1), "1M");

    QObject::connect(
        ibM15, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);
    
    QObject::connect(
        ibH1, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);

    QObject::connect(
        ibH4, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);

    QObject::connect(
        ibD1, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);

    QObject::connect(
        ibW1, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);

    QObject::connect(
        ibMon1, &IntervalButton::notifyInterval,
        this, &IntervalControl::handleIntervalChange);

    layout->addWidget(ibM15);
    layout->addWidget(ibH1);
    layout->addWidget(ibH4);
    layout->addWidget(ibD1);
    layout->addWidget(ibW1);
    layout->addWidget(ibMon1);
    layout->addStretch(1);
}

void IntervalControl::setupLabel() {
    label = new QLabel("Time");
    label->setObjectName("chartTimeLabel");
    label->setFont(
        Settings::App::getInstance()->
            getChartSettings().getChartLabelFont());
    label->setAlignment(Qt::AlignLeft);
}

void IntervalControl::handleIntervalChange(qint64 iSecs) {
    controller->setTimeLength(iSecs);
}

qint64 IntervalControl::getIntervalValue(IntervalControl::INTERVAL i) {
    switch(i){
        case IntervalControl::INTERVAL::m_15:
            return 900;
        case IntervalControl::INTERVAL::h_1:
            return 3600;
        case IntervalControl::INTERVAL::h_4:
            return 14400;
        case IntervalControl::INTERVAL::d_1:
            return 86400;
        case IntervalControl::INTERVAL::w_1:
            return 604800;
        case IntervalControl::INTERVAL::M_1:
            return 2592000;
    }
}