
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    controller = std::make_unique<Controller>();

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    pageMenu = std::make_unique<PageMenu>(stackedWidget, this, controller.get());
    pageCreate = std::make_unique<PageCreate>(stackedWidget, this, controller.get());
    pageSim = std::make_unique<PageSim>(stackedWidget, this, controller.get());

    stackedWidget->addWidget(pageMenu.get());
    stackedWidget->addWidget(pageSim.get());
    stackedWidget->addWidget(pageCreate.get());
    setCentralWidget(stackedWidget);

    connect(stackedWidget, &QStackedWidget::currentChanged, [=](int index) {
        adjustSize();
    });

}
#include <iostream>

MainWindow::~MainWindow() {

}
