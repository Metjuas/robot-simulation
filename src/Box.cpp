#include "Box.hpp"

#define SPAWN_OFFSET 0

Box::Box(int posX, int posY)
{
    this->x = posX;
    this->y = posY;
}

void Box::spawn(QGraphicsScene* scene) {
    //create a new sprite and add it to the scene
    QImage image(":assets/Box.png");
    int width = 64;//image.width();
    int height = 64;//image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/Box.png", nullptr, this->x-(width/2)+SPAWN_OFFSET, this->y-(height/2));
    
    scene->addItem(sprite);
}

void Box::despawn(QGraphicsScene* scene)
{
    scene->removeItem(sprite);
}