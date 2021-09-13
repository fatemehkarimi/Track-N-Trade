#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "main_window.h"

MainWindow::MainWindow(Settings::Window* window_setting,
                        Controller* controller, Exchange* exchangeModel) {
    this->controller = controller;
    this->exchangeModel = exchangeModel;
    window = new QWidget();
    settings = window_setting;
    setUpWindow();
}

void MainWindow::setUpWindow() {
    window = new QWidget();
    window->resize(settings->windowSize());

    QHBoxLayout* main_layout = new QHBoxLayout(window);
    exchange_menu = new QComboBox();
    main_layout->addWidget(exchange_menu);
    QObject::connect(exchange_menu, QOverload<int>::of(&QComboBox::activated),
        this, &MainWindow::exchangeChanged);

    QVBoxLayout* coin_layout = new QVBoxLayout();
    main_layout->addLayout(coin_layout);

    coin_table = new QTableWidget();
    coin_table->insertColumn(0);
    coin_layout->addWidget(coin_table);

    main_layout->setStretchFactor(exchange_menu, 1);
    main_layout->setStretchFactor(coin_layout, 1);

    fetchExchangeList();
}

void MainWindow::show() {
    window->show();
}

void MainWindow::setExchangeMenuOptions(QStringList options) {
    exchange_menu->addItems(options);
}

void MainWindow::fetchExchangeList() {
    QObject::connect(exchangeModel, &Exchange::exchangeListReady,
                    this, &MainWindow::exchangeListFetched);
    exchangeModel->getExchangeList();
}

void MainWindow::exchangeListFetched(QMap <QString, Exchange*> list) {
    QObject::disconnect(exchangeModel, &Exchange::exchangeListReady,
                    this, &MainWindow::exchangeListFetched);

    QStringList exchange_name_list;
    for(auto x = list.begin(); x != list.end(); ++x) {
        Exchange* e = x.value();
        if(e->getName() != nullptr)
            exchange_name_list.append(e->getName());
    }
    setExchangeMenuOptions(exchange_name_list);
}

void MainWindow::exchangeChanged(int index) {
    controller->setExchange(exchange_menu->currentText());
}

void MainWindow::clearCoinTable() {
    coin_table->setRowCount(0);
    coin_table->clearContents();
}

void MainWindow::addCoinToTable(Coin* coin) {
    QString title = coin->name() + "(" + coin->symbol() + ")";
    coin_table->insertRow(coin_table->rowCount());
    QTableWidgetItem* itm = new QTableWidgetItem(title);
    coin_table->setItem(coin_table->rowCount() - 1, 0, itm);
}