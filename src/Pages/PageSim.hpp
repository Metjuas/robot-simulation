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
#include <iostream>
#include <QPointer>
#include <QShowEvent>
#include <QHideEvent>
#include "CustomGraphicsView.hpp"

#include "CustomGraphicsView.hpp"

class PageSim : public QWidget
{
    Q_OBJECT
    public:
    PageSim(QStackedWidget *stackedWidget, QWidget *parent = nullptr, Controller *controller = nullptr);
    ~PageSim();
        
    protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event);

    private slots:
        void handleMouseClick(int x, int y);

    private:
    bool robotSelectGUI(bool toggle);

    QVBoxLayout *vLayout;
    QStackedWidget *m_stackedWidget;
    QTimer *timer;
    CustomGraphicsView *view;
    QGridLayout *gridLayout;
    Controller *controller;

    //robot controll Widgets
    QPushButton *go_button;
    QPushButton *left_button;
    QPushButton *right_button;

};