#include "tracker.h"

Tracker::Tracker(int watchPeriod)
    : watchPeriod(watchPeriod)
{
    QObject::connect(&timer, &QTimer::timeout, this, &Tracker::handleTimeOut);
}

void Tracker::handleTimeOut() {
    // you may use a state pattern here later.
    if(state == STATE::RUNNING)
        this->run();
    else if(state == STATE::STOPPED)
        this->stop();
}

void Tracker::run() {
    state = STATE::RUNNING;
    performAction();
    timer.start();
}

void Tracker::stop() {
    state = STATE::STOPPED;
    timer.stop();
}

Tracker::STATE Tracker::getState() {
    return state;
}