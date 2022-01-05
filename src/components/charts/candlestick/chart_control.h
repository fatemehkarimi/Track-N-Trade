#ifndef CHART_CONTROL_H
#define CHART_CONTROL_H

#include <QHBoxLayout>
#include <QLabel>
#include <settings/settings_app.h>
#include "controller_candlestick.h"
#include "button_interval.h"

class CandleStickController;

class ChartControl : public QWidget
{
public:
    explicit ChartControl(CandleStickController* controller);

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