#ifndef INTERVAL_CONTROLLER_H
#define INTERVAL_CONTROLLER_H

#include <QLabel>
#include <QHBoxLayout>
#include <settings/settings_app.h>
#include <utils/time_interval.h>
#include "button_interval.h"


class IntervalController : public QWidget
{
    Q_OBJECT
public:
    enum INTERVAL {
        m_15,
        h_1,
        h_4,
        d_1,
        w_1,
        M_1,
    };

    explicit IntervalController();
    qint64 getIntervalValue(INTERVAL i);  // Interval value is in secs
    INTERVAL getSelectedInterval();
    void reset();
    QDateTime getStartTime();
    QDateTime getEndTime();

private slots:
    void handleIntervalChange(qint64 iSecs);

signals:
    void intervalChanged();

private:
    void setupLabel();
    QHBoxLayout* layout;
    QLabel* label;
    IntervalButton* ibM15 = nullptr;
    IntervalButton* ibH1 = nullptr;
    IntervalButton* ibH4 = nullptr;
    IntervalButton* ibD1 = nullptr;
    IntervalButton* ibW1 = nullptr;
    IntervalButton* ibMon1 = nullptr;

    INTERVAL selectedInterval = INTERVAL::d_1;
    TimeInterval interval;
};

#endif