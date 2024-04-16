
#include "MainWindow.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    controller = std::make_unique<Controller>();

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    pageMenu = new PageMenu(stackedWidget, this);
    pageCreate = new PageCreate(stackedWidget, this, controller.get());

    // pageSim = std::make_unique<PageSim>(this, controller.get());

    stackedWidget->addWidget(pageMenu);
    // stackedWidget->addWidget(pageSim.get());
    stackedWidget->addWidget(pageCreate);
    setCentralWidget(stackedWidget);

    resize(300, 500);
}

MainWindow::~MainWindow() {
    std::cerr << "MainWindow destructor start" << std::endl;


    std::cerr << "MainWindow destructor end" << std::endl;
}
