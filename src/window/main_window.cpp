#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "main_window.h"

MainWindow::MainWindow(Settings::Window* window_setting, Exchange* exchangeModel) {
    this->exchangeModel = exchangeModel;
    window = new QWidget();
    settings = window_setting;
    setUpWindow();
}

void MainWindow::setUpWindow() {
    window = new QWidget();
    window->resize(settings->windowSize());

    QHBoxLayout* main_layout = new QHBoxLayout(window);
    exchange_menu = new QComboBox(window);
    main_layout->addWidget(exchange_menu);
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