#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <QTimer>
#include <tuple>


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
        std::tuple<QList<QGraphicsItem*>, QList<QGraphicsItem*>, bool> detectCollision(QGraphicsScene* scene);
        //getters
        int getPosX() { return posX; }
        int getPosY() { return posY; }
        void simulate(QGraphicsScene *scene);
        
        std::string getRobotName() { return robotName; }
        int getDistance() { return distance; }
        RotationDirection getDirection() { return direction; }
        int getRotation() { return rotationAngle; }
        //setters
        void setRobotName(std::string name) { this->robotName = name; }
        void setDistance(int distance) { this->distance = distance; }
        void setDirection(RotationDirection direction) { this->direction = direction; setSpriteRotation();}
        void setRotation(int rotation) { this->rotationAngle = rotation; setSpriteRotation();}
        void setSpriteRotation();
        std::string getSaveString();
        void select();
        void unselect();
        void playerControl(QGraphicsScene *scene);

        bool playerGo = false;
        bool playerLeft = false;
        bool playerRight = false;
    private:
        int posX;
        int posY;
        int distance;
        std::string robotName;
        RotationDirection direction;
        int rotationAngle;
        Sprite *sprite = nullptr;
        bool is_rotating = false;
        int rotation_checker = 0;
        bool collision = false;
};
            