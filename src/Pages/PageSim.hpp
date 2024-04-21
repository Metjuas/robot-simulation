#pragma once

#include <QWidget>
#include <QLabel> 
#include <QPushButton> 
#include <QTimer>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Controller.hpp"
#include <QDebug>
#include <QDir>
#include "Sprite.hpp"
#include "Robot.hpp"
#include <iostream>
#include <QPointer>
#include <QShowEvent>


class PageSim : public QWidget
{
    Q_OBJECT;
    public:
        PageSim(QWidget *parent = nullptr, Controller *controller = nullptr);
        ~PageSim();

    private:
        QGraphicsView *view;
        Controller *controller;
    protected:
        void showEvent(QShowEvent *event) override;

};