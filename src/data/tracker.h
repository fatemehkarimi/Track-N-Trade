#ifndef TRACKER_H
#define TRACKER_H

#include <QtWidgets>
#include <QTime>

class Tracker : public QObject {
    Q_OBJECT
public:
    enum STATE {
        STOPPED,
        RUNNING
    };

    void run();
    void stop();
    STATE getState();
    virtual void performAction() = 0;

protected:
    Tracker(int watchPeriod);

private slots:
    void handleTimeOut();

private:
    QTimer timer;
    int watchPeriod;    // watch period in msecs
    STATE state = STATE::STOPPED;
};

#endif