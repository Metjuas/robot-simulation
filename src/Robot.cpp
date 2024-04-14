#include "Robot.hpp"
#include <QGraphicsScene>

Robot::Robot(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

void Robot::spawn(QGraphicsScene* scene) {
    sprite = new Sprite(":assets/RobotAlly.png", nullptr, this->posX, this->posY);
    sprite->setRotation(90); 
    scene->addItem(sprite);
}

void Robot::move() {
    if (sprite) { // Check if sprite is not nullptr
        sprite->setPos(sprite->x() + 1, sprite->y());
    }
}

void Robot::rotate() {
    if (sprite) { // Check if sprite is not nullptr
        //rotate my sprite
        sprite->setRotation(sprite->rotation() + 1);
    }
}

