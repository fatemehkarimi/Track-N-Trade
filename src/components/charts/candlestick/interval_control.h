#ifndef INTERVAL_CONTROL_H
#define INTERVAL_CONTROL_H

#include <QHBoxLayout>
#include <QLabel>
#include <settings/settings_app.h>
#include "controller_candlestick.h"
#include "button_interval.h"

class CandleStickController;

class IntervalControl : public QWidget
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

    explicit IntervalControl(CandleStickController* controller);
    qint64 getIntervalValue(INTERVAL i);  // Interval value is in secs

private slots:
    void handleIntervalChange(qint64 iSecs);

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
    CandleStickController* controller;
};

#endif