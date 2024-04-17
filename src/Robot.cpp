#include "Robot.hpp"
#include <iostream>

#define SPAWN_OFFSET 5

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
    //create a new sprite and add it to the scene
    QImage image(":assets/RobotAlly.png");
    int width = image.width();
    int height = image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/RobotAlly.png", nullptr, this->posX-(width/2)+SPAWN_OFFSET, this->posY-(height/2));
    
    scene->addItem(sprite);
}

void Robot::move() {
    if (sprite) { 
        //calculating new position based on current rotation
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
