
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    pageMenu = new PageMenu(stackedWidget, this);
    pageCreate = new PageCreate(stackedWidget, this);
    pageSim = new PageSim(this);

    stackedWidget->addWidget(pageMenu);
    stackedWidget->addWidget(pageSim);
    stackedWidget->addWidget(pageCreate);

    setCentralWidget(stackedWidget);

    resize(300, 500);
}
#include <iostream>

MainWindow::~MainWindow() {
    if(pageMenu != nullptr){
        delete pageMenu;
    }
    if(pageCreate != nullptr){
        delete pageCreate;
    }
    if(pageSim != nullptr){
        delete pageSim;
    }
}
