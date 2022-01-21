#ifndef INTERVAL_CONTROLLER_H
#define INTERVAL_CONTROLLER_H

#include <QLabel>
#include <QHBoxLayout>
#include <settings/settings_app.h>
#include <utils/time_interval.h>
#include "button_interval.h"
#include "chart_common.h"


class IntervalController : public QWidget
{
    Q_OBJECT
public:

    explicit IntervalController();
    candlestick::INTERVAL getSelectedInterval();
    void reset();
    QDateTime getStartTime();
    QDateTime getEndTime();

private slots:
    void handleIntervalChange(candlestick::INTERVAL i);

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

    candlestick::INTERVAL selectedInterval = candlestick::INTERVAL::d_1;
    TimeInterval interval;
};

#endif