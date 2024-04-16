#include "Robot.hpp"
#include <iostream>

Robot::Robot(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

Robot::~Robot() {
    //if the sprite exists, delete it

    if (sprite != nullptr) {
        delete sprite;
    }
}  



void Robot::spawn(QGraphicsScene* scene) {
    
    QImage image(":assets/RobotAlly.png");
    int width = image.width();
    int height = image.height();

    sprite = new Sprite(":assets/RobotAlly.png", nullptr, this->posX-(width/2), this->posY-(height/2));
    
    scene->addItem(sprite);
}

void Robot::move() {
    if (sprite) { 
      
        double rotation = sprite->rotation() * M_PI / 180.0;

        double newX = sprite->x() + cos(rotation);
        double newY = sprite->y() + sin(rotation);

        sprite->setPos(newX, newY);
    }
}

void Robot::rotate() {
    if (sprite) { 
        //rotate my sprite
        sprite->setRotation(sprite->rotation() + 3);
    }
}

bool Robot::detectCollision(QGraphicsScene* scene) {
    scene = scene;
    return false;
}
