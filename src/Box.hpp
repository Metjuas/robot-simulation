// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>

class Box{
public:
    Box(int pos_x, int pos_y);
    void spawn(QGraphicsScene* scene);
    void despawn(QGraphicsScene* scene);
    int getPosX() { return x; }
    int getPosY() { return y; }
    std::string getSaveString();
private:
    int x;
    int y;
    Sprite *sprite;
};