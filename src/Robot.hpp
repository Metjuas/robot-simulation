#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <cmath>

class Robot: public QObject{
    Q_OBJECT;
    public:
        Robot(int posX, int posY);
        void spawn(QGraphicsScene* scene);
        void move();
        void rotate();
        bool detectCollision(QGraphicsScene* scene);

    private:
        int posX;
        int posY;
        Sprite *sprite;
};
            