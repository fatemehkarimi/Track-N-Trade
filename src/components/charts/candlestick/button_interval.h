#ifndef BUTTON_INTERVAL_H
#define BUTTON_INTERVAL_H

#include <QPushButton>
#include <settings/settings_app.h>

class IntervalButton : public QPushButton
{
    Q_OBJECT
public:
    IntervalButton(qint64 i, QString text);
    void handleClicked();

signals:
    void notifyInterval(qint64 value);

private:
    qint64 interval;
};

#endif