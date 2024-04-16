#pragma once 

#include <QWidget>

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QObject> 
#include <QStackedWidget>
#include <memory>

#include "./Pages/PageCreate.hpp"

#include "./Pages/PageMenu.hpp"
#include "./Pages/PageSim.hpp"

#include "Controller.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    std::unique_ptr<PageMenu> pageMenu = nullptr;
    std::unique_ptr<PageCreate> pageCreate = nullptr;
    std::unique_ptr<PageSim> pageSim = nullptr;
    std::unique_ptr<Controller> controller;

};

