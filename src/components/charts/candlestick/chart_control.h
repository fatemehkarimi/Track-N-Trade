#ifndef CHART_CONTROL_H
#define CHART_CONTROL_H

#include <QHBoxLayout>
#include <QLabel>
#include <settings/settings_app.h>
#include "controller_candlestick.h"
#include "button_interval.h"

class CandleStickController;

class ChartControl : public QHBoxLayout
{
public:
    explicit ChartControl(CandleStickController* controller);

private:
    void setupLabel();
    QLabel* label;
    CandleStickController* controller;
};

#endif