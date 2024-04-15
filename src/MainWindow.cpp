
#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    Controller *controller = new Controller();

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    pageMenu = new PageMenu(stackedWidget, this);
    pageCreate = new PageCreate(stackedWidget, this, controller);
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
    if(pageSim != nullptr){
        delete pageSim;
    }
    if(pageCreate != nullptr){
        delete pageCreate;
    }
    //controller is a pointer, dont delete
}
