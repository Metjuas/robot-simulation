#include "Robot.hpp"

Robot::Robot(int posX, int posY ) {
    this->posX = posX;
    this->posY = posY;
}

void Robot::spawn(QWidget *parent) {
    Sprite *sprite = new Sprite(":assets/RobotAlly.png", parent, this->posX, this->posY);
    this->sprite = sprite;
}

void Robot::move() {
    if (sprite) { // Check if sprite is not nullptr
        sprite->move(sprite->x() + 1, sprite->y());
    }
}

void Robot::rotate() {
    if (sprite) { // Check if sprite is not nullptr
        //rotate my sprite
        sprite->setPixmap((*sprite->pixmap()).transformed(QTransform().rotate(90)));
    }
}

