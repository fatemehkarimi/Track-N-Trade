#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <settings/settings_window.h>
#include <data/exchange.h>
#include <data/controller.h>
#include <components/table_market.h>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow(Settings::Window* window_setting,
                Controller* controller, Exchange* ecxhangeModel);
    void setUpWindow();
    void show();
    void setExchangeMenuOptions(QStringList options);
    MarketTable* getMarketTable();

private slots:
    void exchangeListFetched(QMap <QString, std::shared_ptr <Exchange> >);
    void exchangeChanged(int index);

private:
    void fetchExchangeList();

    Controller* controller;
    Exchange* exchangeModel;
    QWidget* window;
    QComboBox* exchange_menu;
    MarketTable* marketTable;
    Settings::Window* settings;
};

#endif