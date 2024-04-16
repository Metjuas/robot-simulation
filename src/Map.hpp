#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QDebug>
#include "Controller.hpp"


class Map
{
public:
    Map(Controller* controller, QWidget *parent = nullptr);
    ~Map();
private:
    QWidget *m_parent;
    Controller* m_controller;
};