#ifndef THROBBER_H
#define THROBBER_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QHBoxLayout>
#include <QTimer>
#include <QColor>

class Throbber : public QWidget {
public:
    explicit Throbber();

private slots:
    void handleTimeout();

private:
    void addSlice();

    const int TIMER_INTERVAL = 120;
    const int COUNT_SLICES = 13;
    const double TOTAL_VALUE = 120;
    const QColor SHADES[12] = {
        QColor(0, 56, 91, 255),
        QColor(0, 71, 103, 255),
        QColor(1, 91, 126, 255),
        QColor(0, 112, 144, 255),
        QColor(0, 138, 159, 255),
        QColor(22, 174, 198, 255),
        QColor(45, 190, 211, 255),
        QColor(79, 200, 219, 255),
        QColor(107, 215, 227, 255),
        QColor(141, 231, 239, 255),
        QColor(149, 240, 245, 255),
        QColor(199, 247, 247, 255)
    };

    const QColor EMPTY_SHADE = QColor(225, 230, 237);

    int current = 0;

    QTimer timer;
    QtCharts::QPieSeries* series;
    QtCharts::QChartView* view;
};


#endif