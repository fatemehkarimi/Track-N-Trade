#include "chart_control.h"

ChartControl::ChartControl(CandleStickController* controller) {
    this->controller = controller;
    layout = new QHBoxLayout(this);

    setupLabel();
    layout->addWidget(label);

    ibM15 = new IntervalButton(IntervalButton::m_15);
    ibH1 = new IntervalButton(IntervalButton::h_1);
    ibH4 = new IntervalButton(IntervalButton::h_4);
    ibD1 = new IntervalButton(IntervalButton::d_1);
    ibW1 = new IntervalButton(IntervalButton::w_1);
    ibMon1 = new IntervalButton(IntervalButton::M_1);

    layout->addWidget(ibM15);
    layout->addWidget(ibH1);
    layout->addWidget(ibH4);
    layout->addWidget(ibD1);
    layout->addWidget(ibW1);
    layout->addWidget(ibMon1);
    layout->addStretch(1);
}

void ChartControl::setupLabel() {
    label = new QLabel("Time");
    label->setObjectName("chartTimeLabel");
    label->setFont(
        Settings::App::getInstance()->
            getChartSettings().getChartLabelFont());
    label->setAlignment(Qt::AlignLeft);
}