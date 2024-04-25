#pragma once

#include "Sprite.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <QTimer>
#include <tuple>
#include <string>

enum RotationDirection{
    LEFT,
    RIGHT
};

class Robot: public QObject{
    Q_OBJECT;
    public:
        Robot(int pos_x, int pos_y);
        Robot(std::string name, int pos_x, int pos_y, int rotation, int distance, RotationDirection direction);
        ~Robot();
        void spawn(QGraphicsScene* scene);
        void despawn(QGraphicsScene* scene);
        void move();
        void rotate();
        std::tuple<QList<QGraphicsItem*>, QList<QGraphicsItem*>, bool> detectCollision(QGraphicsScene* scene);
        //getters
        int getPosX() { return pos_x; }
        int getPosY() { return pos_y; }
        void simulate(QGraphicsScene *scene);
        
        std::string getRobotName() { return robot_name; }
        int getDistance() { return distance; }
        RotationDirection getDirection() { return direction; }
        int getRotation() { return rotation_angle; }
        int getRobotRotation(){return robot_rotation;}
        //setters
        void setRobotName(std::string name) { this->robot_name = name; }
        void setDistance(int distance) { this->distance = distance; }
        void setDirection(RotationDirection direction) { this->direction = direction; setSpriteRotation();}
        void setRotation(int rotation) { this->rotation_angle = rotation; setSpriteRotation();}
        void setRobotRotation(int rotation){this->robot_rotation = rotation;}
        void setSpriteRotation();
        std::string getSaveString();
        void select();
        void unselect();
        void playerControl(QGraphicsScene *scene);

        bool player_go;
        bool player_left;
        bool player_right;
    private:
        int pos_x;
        int pos_y;
        int distance;
        std::string robot_name;
        RotationDirection direction;
        int rotation_angle;
        Sprite *sprite;
        bool is_rotating;
        int rotation_checker;
        bool collision;
        int robot_rotation;
};
            