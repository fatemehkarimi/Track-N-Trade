#include "chart_control.h"

ChartControl::ChartControl() {
    setupLabel();
    this->addWidget(label);
}

void ChartControl::setupLabel() {
    label = new QLabel("Time");
    label->setObjectName("chartTimeLabel");
    label->setFont(
        Settings::App::getInstance()->
            getChartSettings().getChartLabelFont());
    label->setAlignment(Qt::AlignLeft);
}