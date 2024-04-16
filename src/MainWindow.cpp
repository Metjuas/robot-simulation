
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    controller = std::make_unique<Controller>();

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    pageMenu = std::make_unique<PageMenu>(stackedWidget, this);
    pageCreate = std::make_unique<PageCreate>(stackedWidget, this, controller.get());
    pageSim = std::make_unique<PageSim>(this, controller.get());

    stackedWidget->addWidget(pageMenu.get());
    stackedWidget->addWidget(pageSim.get());
    stackedWidget->addWidget(pageCreate.get());
    setCentralWidget(stackedWidget);

    resize(300, 500);
}
#include <iostream>

MainWindow::~MainWindow() {

}
