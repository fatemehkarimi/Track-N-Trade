#include "button_interval.h"


IntervalButton::IntervalButton(IntervalButton::INTERVAL i) {
    this->interval = i;
    QString text = "";
    switch(interval){
        case INTERVAL::m_15:
            text = "15m";
            break;
        case INTERVAL::h_1:
            text = "1h";
            break;
        case INTERVAL::h_4:
            text = "4h";
            break;
        case INTERVAL::d_1:
            text = "1d";
            break;
        case INTERVAL::w_1:
            text = "1w";
            break;
        case INTERVAL::M_1:
            text = "1M";
            break;
    }
    this->setText(text);
    QObject::connect(
        this, &QPushButton::clicked,
        this, &IntervalButton::setChartInterval);
}

void IntervalButton::setChartInterval() {
    
}