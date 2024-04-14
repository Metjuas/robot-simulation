
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    setFixedSize(800, 400);

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    PageMenu *pageMenu = new PageMenu(stackedWidget, nullptr);
    PageSim *pageSim = new PageSim(nullptr);

    stackedWidget->addWidget(pageMenu);
    stackedWidget->addWidget(pageSim);

    setCentralWidget(stackedWidget);
}