#pragma once

#include <QWidget>
#include <QLabel> 
#include <QPushButton> 
#include <QTimer>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Controller.hpp"

class PageSim : public QWidget
{
    Q_OBJECT;
    public:
    PageSim(QWidget *parent = nullptr, Controller *controller = nullptr);
    ~PageSim();
  
    private:
    QTimer *timer;
    QGraphicsView view;

};