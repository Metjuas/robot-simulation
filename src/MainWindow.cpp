
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    PageMenu *pageMenu = new PageMenu(stackedWidget, this);
    PageCreate *pageCreate = new PageCreate(stackedWidget, this);
    PageSim *pageSim = new PageSim(this);

    stackedWidget->addWidget(pageMenu);
    stackedWidget->addWidget(pageSim);
    stackedWidget->addWidget(pageCreate);

    setCentralWidget(stackedWidget);

    resize(300, 500);
}