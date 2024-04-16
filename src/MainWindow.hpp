#pragma once 

#include <QWidget>

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QObject> 
#include <QStackedWidget>

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
    PageMenu *pageMenu = nullptr;
    PageCreate *pageCreate = nullptr;
    PageSim *pageSim = nullptr;
    Controller *controller;

};

