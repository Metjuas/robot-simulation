// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#pragma once

#include <QWidget>
#include <QLabel> 
#include <QPushButton> 
#include <QTimer>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedWidget>

#include "Controller.hpp"
#include <QDebug>
#include <QDir>
#include "Sprite.hpp"
#include "Robot.hpp"
#include <QPointer>
#include <QShowEvent>
#include <QHideEvent>
#include "CustomGraphicsView.hpp"
#include <iostream>


class PageSim : public QWidget
{
    Q_OBJECT
    public:
    PageSim(QStackedWidget *stacked_widget, QWidget *parent = nullptr, Controller *controller = nullptr);
        
    protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event);

    private slots:
        void handleMouseClick(int x, int y);

    private:
    void robotSelectGUI(bool toggle);

    QVBoxLayout *v_layout;
    QStackedWidget *stacked_widget;
    QTimer *timer;
    CustomGraphicsView *view;
    QGridLayout *grid_layout;
    Controller *controller;

    //robot controll Widgets
    QPushButton *go_button;
    QPushButton *left_button;
    QPushButton *right_button;

};