#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <settings/settings_window.h>
#include <data/exchange.h>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    MainWindow(Settings::Window* window_setting, Exchange* ecxhangeModel);
    void setUpWindow();
    void show();
    void setExchangeMenuOptions(QStringList options);

private slots:
    void exchangeListFetched(QMap <QString, Exchange*>);

private:
    void fetchExchangeList();

    Exchange* exchangeModel;
    QWidget* window;
    QComboBox* exchange_menu;
    Settings::Window* settings;
};

#endif