#ifndef BUTTON_INTERVAL_H
#define BUTTON_INTERVAL_H

#include <QPushButton>
#include <settings/settings_app.h>

class IntervalButton : public QPushButton
{
public:
    enum INTERVAL {
        m_15 = 900,
        h_1 = 3600,
        h_4 = 14400,
        d_1 = 86400,
        w_1 = 604800,
        M_1 = 2592000
    };

    IntervalButton(INTERVAL i);
    void setChartInterval();

private:
    INTERVAL interval;
};

#endif