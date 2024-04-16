#pragma once 

#include <QWidget>

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QObject> 
#include <QStackedWidget>

// #include "./Pages/PageCreate.hpp"

// #include "./Pages/PageMenu.hpp"
// #include "./Pages/PageSim.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private:
    // PageMenu* pageMenu = nullptr;
    // PageCreate* pageCreate = nullptr;

    // std::unique_ptr<PageSim> pageSim = nullptr;
    // std::unique_ptr<Controller> controller;

};

