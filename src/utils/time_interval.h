#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

#include <QtWidgets>
#include <QDateTime>

class TimeInterval {
public:
    explicit TimeInterval();
    TimeInterval(QDateTime startTime, qint64 length);

    void setStartTime(QDateTime startTime);
    void setLength(qint64 length);

    QDateTime getStartTime();
    QDateTime getEndTime();
    qint64 getLength();

    void moveIntervalForward();
    void moveIntervalBackward();

private:
    qint64 startTime;   // start time is inclusive, but end time is exclusive
    qint64 length;      // unit of length: secs
};

#endif