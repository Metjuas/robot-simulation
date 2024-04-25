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
private:
    std::unique_ptr<PageMenu> page_menu = nullptr;
    std::unique_ptr<PageCreate> page_create = nullptr;
    std::unique_ptr<PageSim> page_sim = nullptr;
    std::unique_ptr<Controller> controller;

};

