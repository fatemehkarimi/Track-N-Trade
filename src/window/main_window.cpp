#include "main_window.h"

MainWindow::MainWindow(Settings::Window* window_setting) {
    window = new QWidget();
    settings = window_setting;
    setUpWindow();
}

void MainWindow::setUpWindow() {
    window = new QWidget();
    window->resize(settings->windowSize());
}

void MainWindow::show() {
    window->show();
}