#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <settings/settings_window.h>
#include <data/api_manager.h>
#include <data/controller.h>
#include <data/container.h>
#include <components/table_market.h>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow(Settings::Window* window_setting,
                Controller* controller, APIManager* apiModel);
    void setUpWindow();
    void show();
    void setExchangeMenuOptions(QStringList options);
    MarketTable* getMarketTable();

private slots:
    void exchangeListFetched(Container <Exchange>);
    void exchangeChanged(int index);

private:
    void fetchExchangeList();

    Controller* controller;
    APIManager* apiModel;
    QWidget* window;
    QComboBox* exchangeMenu;
    MarketTable* marketTable;
    Settings::Window* settings;
};

#endif