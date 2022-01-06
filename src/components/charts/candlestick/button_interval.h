#ifndef BUTTON_INTERVAL_H
#define BUTTON_INTERVAL_H

#include <QPushButton>
#include <settings/settings_app.h>

class IntervalButton : public QPushButton
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

    IntervalButton(INTERVAL i);
    qint64 getIntervalValue();  // Interval value is in secs
    void handleClicked();

signals:
    void notifyInterval(qint64 value);

private:
    INTERVAL interval;
};

#endif