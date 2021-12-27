#include "time_interval.h"

TimeInterval::TimeInterval() {}

TimeInterval::TimeInterval(QDateTime startTime, qint64 length) {
    setStartTime(startTime);
    setLength(length);
}

void TimeInterval::setStartTime(QDateTime startTime) {
    this->startTime = startTime.toSecsSinceEpoch();
}

void TimeInterval::setEndTime(QDateTime endTime) {
    this->startTime = endTime.toSecsSinceEpoch() - this->length;
}

void TimeInterval::setLength(qint64 length) {
    this->length = length;
}

QDateTime TimeInterval::getStartTime() {
    QDateTime startTime;
    startTime.setSecsSinceEpoch(this->startTime);
    return startTime;
}

QDateTime TimeInterval::getEndTime() {
    QDateTime endTime;
    endTime.setSecsSinceEpoch(this->startTime + this->length);
    return endTime;
}

qint64 TimeInterval::getLength() {
    return this->length;
}

void TimeInterval::moveIntervalForward() {
    this->startTime = this->startTime + this->length;
}

void TimeInterval::moveIntervalBackward() {
    this->startTime = this->startTime - this->length;
}
