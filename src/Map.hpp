#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QDebug>
#include "Controller.hpp"
#include <iostream>

class Map
{
public:
    Map(Controller* controller, QWidget *parent = nullptr);
    ~Map(){
        std::cerr << "Map destructor" << std::endl;
    };
private:
    QWidget *m_parent;
    Controller* m_controller;
};