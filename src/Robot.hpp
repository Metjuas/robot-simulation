#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <cmath>

enum RotationDirection{
    LEFT,
    RIGHT
};

class Robot: public QObject{
    Q_OBJECT;
    public:
        Robot(int posX, int posY);
        Robot(std::string name, int posX, int posY, int rotation, int distance, RotationDirection direction);
        ~Robot();
        void spawn(QGraphicsScene* scene);
        void despawn(QGraphicsScene* scene);
        void move();
        void rotate();
        bool detectCollision(QGraphicsScene* scene);
        int getPosX() { return posX; }
        int getPosY() { return posY; }
        std::string getSaveString();
    private:
        int posX;
        int posY;
        int distance;
        std::string robotName;
        RotationDirection direction;
        int rotationAngle;

        Sprite *sprite = nullptr;
};
            