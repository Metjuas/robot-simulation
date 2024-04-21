#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "Controller.hpp"



class PageMenu : public QWidget
{
    Q_OBJECT;
    public:
        PageMenu(QStackedWidget *stackedWidget, QWidget *parent = nullptr, Controller *controller = nullptr);
    private:
        QStackedWidget *m_stackedWidget;
        Controller *controller;
};
