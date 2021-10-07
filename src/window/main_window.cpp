#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "main_window.h"

MainWindow::MainWindow(Settings::Window* window_setting,
                        Controller* controller, Exchange* exchangeModel) {
    this->controller = controller;
    this->exchangeModel = exchangeModel;

    QObject::connect(exchangeModel, &Exchange::exchangeListReady,
        this, &MainWindow::exchangeListFetched, Qt::UniqueConnection);

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

    coin_table = new CoinTable("coin_table");
    coin_layout->addWidget(coin_table);

    QObject::connect(coin_table, &CoinTable::coinListUpdated, this, [=](){
        exchange_menu->setEnabled(true);
    });

    main_layout->setStretchFactor(exchange_menu, 1);
    main_layout->setStretchFactor(coin_layout, 1);

    fetchExchangeList();
}

void MainWindow::show() {
    window->show();
}

void MainWindow::setExchangeMenuOptions(QStringList options) {
    exchange_menu->clear();
    exchange_menu->addItems(options);
    controller->setExchange(exchange_menu->currentText());
}

void MainWindow::fetchExchangeList() {
    exchangeModel->getExchangeList();
}

void MainWindow::exchangeListFetched(QMap <QString, std::shared_ptr <Exchange> > list) {
    QStringList exchange_name_list;
    for(auto x = list.begin(); x != list.end(); ++x) {
        std::shared_ptr <Exchange> e = x.value();
        if(e->getName() != nullptr)
            exchange_name_list.append(e->getName());
    }
    setExchangeMenuOptions(exchange_name_list);
}

void MainWindow::exchangeChanged(int) {
    controller->setExchange(exchange_menu->currentText());
    exchange_menu->setEnabled(false);
}
