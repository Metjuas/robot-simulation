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

void Robot::simulate(QGraphicsScene *scene) {
    if(detectCollision(scene)){
        rotation_checker = 50;
        is_rotating = true;
    }
    if(is_rotating){
        rotate();
    }
    else{
        move();
    }
}


void Robot::spawn(QGraphicsScene* scene) {
    //create a new sprite and add it to the scene
    QImage image(":assets/RobotAlly.png");
    int width = image.width();
    int height = image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/RobotAlly.png", nullptr, this->posX-(width/2)+SPAWN_OFFSET, this->posY-(height/2));
    sprite->setTransformOriginPoint(sprite->boundingRect().width() / 2.0, sprite->boundingRect().height() / 2.0);
    
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
    if (sprite && rotation_checker > 0) {
        // Set the point of rotation to the center of the sprite
        sprite->setRotation(sprite->rotation() + 1);
        rotation_checker--;
        if (rotation_checker == 0) {
            is_rotating = false;
        }
    }
}

bool Robot::detectCollision(QGraphicsScene* scene) {
    qreal radius = sprite->boundingRect().width() / 2.0;
    qreal detectionDistance = 30.0;

    // Calculate the center of the detection rectangle
    qreal centerX = sprite->pos().x() + radius + cos(sprite->rotation() * M_PI / 180.0) * (radius + detectionDistance);
    qreal centerY = sprite->pos().y() + radius + sin(sprite->rotation() * M_PI / 180.0) * (radius + detectionDistance);
    // Create the detection rectangle

    QRectF detectionRect(centerX - detectionDistance / 2.0, centerY - detectionDistance / 2.0, detectionDistance, detectionDistance);

    QList<QGraphicsItem*> itemsInFront = scene->items(detectionRect);

    if (!itemsInFront.isEmpty()) {
        qDebug() << "Hello";
        return true;
    }
    return false;
}