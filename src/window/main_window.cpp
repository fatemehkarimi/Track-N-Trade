#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "main_window.h"

MainWindow::MainWindow(Settings::Window* window_setting,
    Controller* controller, APIManager* apiModel)
    : controller(controller),
     apiModel(apiModel),
     settings(window_setting) {

    QObject::connect(apiModel, &APIManager::exchangeListReady,
        this, &MainWindow::exchangeListFetched, Qt::UniqueConnection);
    window = new QWidget();
    setUpWindow();
}

void MainWindow::setUpWindow() {
    window = new QWidget();
    window->resize(settings->windowSize());

    QHBoxLayout* main_layout = new QHBoxLayout(window);
    exchangeMenu = new QComboBox();
    main_layout->addWidget(exchangeMenu);
    QObject::connect(exchangeMenu, QOverload<int>::of(&QComboBox::activated),
        this, &MainWindow::exchangeChanged);

    QVBoxLayout* market_layout = new QVBoxLayout();
    main_layout->addLayout(market_layout);

    marketTable = new MarketTable("market_table");
    market_layout->addWidget(marketTable);

    QObject::connect(marketTable, &MarketTable::assetListUpdated, this, [=](){
        exchangeMenu->setEnabled(true);
    });

    main_layout->setStretchFactor(exchangeMenu, 1);
    main_layout->setStretchFactor(market_layout, 1);

    fetchExchangeList();
}

void MainWindow::show() {
    window->show();
}

MarketTable* MainWindow::getMarketTable() {
    return marketTable;
}

void MainWindow::setExchangeMenuOptions(QList <QPair <QString, QVariant> > options) {
    exchangeMenu->clear();
    for(auto option : options) {
        QString text = option.first;
        QVariant data = option.second;
        exchangeMenu->addItem(text, data);
    }
    QString currentExchangeSymbol = exchangeMenu->currentData().toString();
    controller->setExchange(currentExchangeSymbol);
}

void MainWindow::fetchExchangeList() {
    apiModel->getExchangeList();
}

void MainWindow::exchangeListFetched(Container <Exchange> list) {
    QList < QPair <QString, QVariant> > exchangeList;
    auto iterator = list.createIterator();

    while(iterator.hasNext()) {
        std::shared_ptr <Exchange> exchange = iterator.next();

        // exchange symbol is required to contact with controller
        QVariant exchangeSymbol(exchange->getSymbol());
        QPair <QString, QVariant> pair(exchange->getName(), exchangeSymbol);
        exchangeList.append(pair);
    }
    
    std::sort(exchangeList.begin(), exchangeList.end());
    setExchangeMenuOptions(exchangeList);
}

void MainWindow::exchangeChanged(int) {
    QString currentExchangeSymbol = exchangeMenu->currentData().toString();
    controller->setExchange(currentExchangeSymbol);
    exchangeMenu->setEnabled(false);
}
