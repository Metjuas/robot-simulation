#include "Robot.hpp"
#include <QGraphicsScene>
#include <cmath>

Robot::Robot(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

void Robot::spawn(QGraphicsScene* scene) {
    sprite = new Sprite(":assets/RobotAlly.png", nullptr, this->posX, this->posY);
    scene->addItem(sprite);
}

void Robot::move() {
    if (sprite) { 
        // our sprite is by default rotated by 90
        double rotation = (sprite->rotation()) * M_PI / 180.0;

        double newX = sprite->x() + cos(rotation);
        double newY = sprite->y() + sin(rotation);

        sprite->setPos(newX, newY);
    }
}

void Robot::rotate() {
    if (sprite) { // Check if sprite is not nullptr
        //rotate my sprite
        sprite->setRotation(sprite->rotation() + 1);
    }
}

