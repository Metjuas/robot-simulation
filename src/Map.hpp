// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

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
    
private:
    QWidget *parent;
    Controller* controller;
};