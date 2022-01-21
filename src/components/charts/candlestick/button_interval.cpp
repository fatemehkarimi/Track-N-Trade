#include "button_interval.h"


IntervalButton::IntervalButton(candlestick::INTERVAL i, QString text) {
    this->setObjectName("intervalButton");
    this->interval = i;
    this->setText(text);
    this->setFont(Settings::App::getInstance()->
        getChartSettings().getIntervalButtonFont());

    QObject::connect(
        this, &QPushButton::clicked,
        this, &IntervalButton::handleClicked);
}

void IntervalButton::handleClicked() {
    emit notifyInterval(this->interval);
}