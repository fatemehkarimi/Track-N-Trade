#ifndef THROBBER_H
#define THROBBER_H

#include <QDebug>
#include <QThread>
#include <QGraphicsLayout>
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QHBoxLayout>
#include <QTimer>
#include <QColor>
#include <QApplication>


class SeriesHandler : public QObject {
    Q_OBJECT
public slots:
    void handle(int current) {
        QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
        series->setHoleSize(0.5);

        for(int i = 0; i < current; ++i) {
            QtCharts::QPieSlice* slice = 
                series->append("", TOTAL_VALUE / (COUNT_SLICES - 1));
            slice->setColor(SHADES[i]);
        }

        QtCharts::QPieSlice* emptySlice = series->append(
            "",
            TOTAL_VALUE - series->count() * TOTAL_VALUE / (COUNT_SLICES - 1));
        emptySlice->setColor(EMPTY_SHADE);

        series->moveToThread(QApplication::instance()->thread());
        emit seriesReady(series);
    }

signals:
    void seriesReady(QtCharts::QPieSeries* series);
    
private:
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
};

class Throbber : public QWidget {
    Q_OBJECT
public:
    explicit Throbber(QWidget* parent=nullptr);
    ~Throbber();

private slots:
    void handleTimeout();

signals:
    void updateSeries(int current);

private:
    static void registerAsMetaType();
    void setupView();
    void setupSeriesHandler();
    void handleSeriesUpdate(QtCharts::QPieSeries* series);

    const int COUNT_SLICES = 13;
    const int TIMER_INTERVAL = 120;
    int current = 0;

    SeriesHandler* seriesHandler = nullptr;
    QThread seriesHandlerThread;

    QTimer timer;
    QtCharts::QChartView* view;
};

Q_DECLARE_METATYPE(QtCharts::QPieSeries*)

#endif