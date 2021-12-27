#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QVariant>
#include <data/api_manager.h>
#include <data/controller.h>
#include <data/container.h>
#include <settings/settings_window.h>
#include <components/tables/table_market/table_market.h>
#include <components/tables/table_price/table_price.h>
#include <components/search_box/search_box.h>
#include <components/charts/candlestick/controller_candlestick.h>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow(Settings::Window* window_setting,
                Controller* controller, APIManager* apiModel);
    void setUpWindow();
    void show();
    void setExchangeMenuOptions(QList <QPair <QString, QVariant> > options);
    MarketTable* getMarketTable();
    PriceTable* getPriceTable();
    CandleStickController* getCandleStickController();

public slots:
    void handlePairSelected(QString pairSymbol);

private slots:
    void exchangeListFetched(Container <Exchange>);
    void exchangeChanged(int index);

private:
    void fetchExchangeList();
    void setUpExchangeMenu(QString objectName);
    void setUpPriceTable(QString objectName);
    void setUpCandleStick(QString objectName);

    Controller* controller;
    APIManager* apiModel;
    QWidget* window;
    QComboBox* exchangeMenu;
    MarketTable* marketTable;
    PriceTable* priceTable;
    CandleStickController* candlestickController;
    Settings::Window* settings;
};

#endif