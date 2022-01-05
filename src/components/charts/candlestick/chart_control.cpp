#include "chart_control.h"

ChartControl::ChartControl(CandleStickController* controller) {
    this->controller = controller;

    setupLabel();
    this->addWidget(label);

    IntervalButton* ib1 = new IntervalButton(IntervalButton::m_15);
    IntervalButton* ib2 = new IntervalButton(IntervalButton::h_1);
    IntervalButton* ib3 = new IntervalButton(IntervalButton::h_4);
    IntervalButton* ib4 = new IntervalButton(IntervalButton::d_1);
    IntervalButton* ib5 = new IntervalButton(IntervalButton::w_1);
    IntervalButton* ib6 = new IntervalButton(IntervalButton::M_1);

    this->addWidget(ib1);
    this->addWidget(ib2);
    this->addWidget(ib3);
    this->addWidget(ib4);
    this->addWidget(ib5);
    this->addWidget(ib6);
    this->addStretch(1);
}

void ChartControl::setupLabel() {
    label = new QLabel("Time");
    label->setObjectName("chartTimeLabel");
    label->setFont(
        Settings::App::getInstance()->
            getChartSettings().getChartLabelFont());
    label->setAlignment(Qt::AlignLeft);
}