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

void MainWindow::setExchangeMenuOptions(QStringList options) {
    exchangeMenu->clear();
    exchangeMenu->addItems(options);
    // controller->setExchange(exchangeMenu->currentText());
}

void MainWindow::fetchExchangeList() {
    apiModel->getExchangeList();
}

void MainWindow::exchangeListFetched(Container <Exchange> list) {
    QStringList nameList;
    auto iterator = list.createIterator();

    while(iterator.hasNext()) {
        std::shared_ptr <Exchange> exchange = iterator.next();
        nameList.append(exchange->getName());
    }
    nameList.sort();
    setExchangeMenuOptions(nameList);
}

void MainWindow::exchangeChanged(int) {
    controller->setExchange(exchangeMenu->currentText());
    exchangeMenu->setEnabled(false);
}
