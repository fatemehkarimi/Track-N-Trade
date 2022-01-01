#ifndef CHART_CONTROL_H
#define CHART_CONTROL_H

#include <QHBoxLayout>
#include <QLabel>
#include <settings/settings_app.h>

class ChartControl : public QHBoxLayout
{
public:
    explicit ChartControl();

private:
    void setupLabel();

    QLabel* label;
};

#endif