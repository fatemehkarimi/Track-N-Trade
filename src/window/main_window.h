#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <settings/settings_window.h>
#include <data/exchange.h>
#include <data/controller.h>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    MainWindow(Settings::Window* window_setting,
                Controller* controller, Exchange* ecxhangeModel);
    void setUpWindow();
    void show();
    void setExchangeMenuOptions(QStringList options);

    void addCoinToTable(Coin* coin);
    void clearCoinTable();

private slots:
    void exchangeListFetched(QMap <QString, Exchange*>);
    void exchangeChanged(int index);

private:
    void fetchExchangeList();

    Controller* controller;
    Exchange* exchangeModel;
    QWidget* window;
    QComboBox* exchange_menu;
    QTableWidget* coin_table;
    Settings::Window* settings;
};

#endif