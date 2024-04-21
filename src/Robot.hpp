#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <cmath>

class Robot: public QObject{
    Q_OBJECT;
    public:
        Robot(int posX, int posY);
        ~Robot();
        void spawn(QGraphicsScene* scene);
        void move();
        void rotate();
        bool detectCollision(QGraphicsScene* scene);
        int getPosX() { return posX; }
        int getPosY() { return posY; }
        void simulate(QGraphicsScene *scene);
    private:
        int posX;
        int posY;
        Sprite *sprite = nullptr;
        bool is_rotating = false;
        int rotation_checker = 0;
};
            