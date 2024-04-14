#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QObject> // Include the missing header file
#include <QStackedWidget>

#include "./Pages/PageMenu.hpp"
#include "./Pages/PageSim.hpp"
#include "./Pages/PageCreate.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

};


#endif 