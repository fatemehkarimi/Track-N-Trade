#ifndef BUTTON_INTERVAL_H
#define BUTTON_INTERVAL_H

#include <QPushButton>
#include <settings/settings_app.h>
#include "chart_common.h"
class IntervalButton : public QPushButton
{
    Q_OBJECT
public:
    IntervalButton(candlestick::INTERVAL i, QString text);
    void handleClicked();

signals:
    void notifyInterval(candlestick::INTERVAL i);

private:
    candlestick::INTERVAL interval;
};

#endif