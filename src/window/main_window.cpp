#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <settings/settings_app.h>
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
    window->setObjectName("mainWindow");
    window->resize(settings->windowSize());

    QHBoxLayout* mainLayout = new QHBoxLayout(window);
    QVBoxLayout* pairInfoLayout = new QVBoxLayout();
    mainLayout->addLayout(pairInfoLayout);

    QVBoxLayout* priceLayout = new QVBoxLayout();
    QVBoxLayout* chartLayout = new QVBoxLayout();

    pairInfoLayout->addLayout(priceLayout);
    pairInfoLayout->addLayout(chartLayout);

    pairInfoLayout->setStretchFactor(priceLayout, 1);
    pairInfoLayout->setStretchFactor(chartLayout, 5);

    setUpExchangeMenu("exchangeMenu");
    setUpPriceTable("priceTable");
    priceLayout->addWidget(exchangeMenu);
    priceLayout->addWidget(priceTable);

    QVBoxLayout* marketLayout = new QVBoxLayout();
    mainLayout->addLayout(marketLayout);

    SearchBox* searchBox = new SearchBox("searchBox");
    marketLayout->addWidget(searchBox);

    marketTable = new MarketTable("marketTable");
    marketLayout->addWidget(marketTable);

    QObject::connect(marketTable, &MarketTable::assetListUpdated, this, [=](){
        exchangeMenu->setEnabled(true);
    });

    QObject::connect(searchBox, &SearchBox::textChanged,
        marketTable, &MarketTable::setFilter);

    mainLayout->setStretchFactor(pairInfoLayout, 1);
    mainLayout->setStretchFactor(marketLayout, 1);

    fetchExchangeList();
}

void MainWindow::setUpExchangeMenu(QString objectName) {
    exchangeMenu = new QComboBox();
    exchangeMenu->setObjectName(objectName);
    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont font = fontSettings.getExchangeMenuFont();
    exchangeMenu->setFont(font);
    
    QObject::connect(exchangeMenu, QOverload<int>::of(&QComboBox::activated),
        this, &MainWindow::exchangeChanged);
}

void MainWindow::setUpPriceTable(QString objectName) {
    priceTable = new PriceTable(objectName);
}

void MainWindow::show() {
    window->show();
}

PriceTable* MainWindow::getPriceTable() {
    return priceTable;
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
    exchangeChanged(exchangeMenu->currentIndex());
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
    marketTable->clear();
}
