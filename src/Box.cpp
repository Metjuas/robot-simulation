#include "Box.hpp"


Box::Box(int pos_x, int pos_y)
{
    sprite = nullptr;
    this->x = pos_x;
    this->y = pos_y;
}

void Box::spawn(QGraphicsScene* scene) {
    //create a new sprite and add it to the scene
    QImage image(":assets/Box.png");
    int width = 64;//image.width();
    int height = 64;//image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/Box.png", nullptr, this->x-(width/2), this->y-(height/2));
    
    scene->addItem(sprite);
}

void Box::despawn(QGraphicsScene* scene)
{
    scene->removeItem(sprite);
}

std::string Box::getSaveString()
{
    std::string out =   "(" +
                        std::to_string(this->x) + "," +
                        std::to_string(this->y) + 
                        ")";
    return out;
}