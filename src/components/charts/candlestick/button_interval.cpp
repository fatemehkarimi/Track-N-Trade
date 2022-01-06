#include "button_interval.h"


IntervalButton::IntervalButton(IntervalButton::INTERVAL i) {
    this->setObjectName("intervalButton");
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
    this->setFont(Settings::App::getInstance()->
        getChartSettings().getIntervalButtonFont());

    QObject::connect(
        this, &QPushButton::clicked,
        this, &IntervalButton::handleClicked);
}

qint64 IntervalButton::getIntervalValue() {
    switch(interval){
        case INTERVAL::m_15:
            return 900;
        case INTERVAL::h_1:
            return 3600;
        case INTERVAL::h_4:
            return 14400;
        case INTERVAL::d_1:
            return 86400;
        case INTERVAL::w_1:
            return 604800;
        case INTERVAL::M_1:
            return 2592000;
    }
}

void IntervalButton::handleClicked() {
    emit notifyInterval(getIntervalValue());
}