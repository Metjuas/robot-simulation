#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "Controller.hpp"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


class PageMenu : public QWidget
{
    Q_OBJECT;
    public:
        PageMenu(QStackedWidget *stacked_widget, QWidget *parent = nullptr, Controller *controller = nullptr);
    private:
        QStackedWidget *stacked_widget;
        Controller *controller;
};
