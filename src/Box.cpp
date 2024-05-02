// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#include "Box.hpp"

const int BOX_SPRITE_WIDTH = 64;
const int BOX_SPRITE_HEIGHT = 64;

/// @brief Constructor for box on position x and y
/// @param pos_x  
/// @param pos_y 
Box::Box(int pos_x, int pos_y)
{
    sprite = nullptr;
    this->x = pos_x;
    this->y = pos_y;
}

/// @brief Spawns box into scene
/// @param scene 
void Box::spawn(QGraphicsScene* scene) {
    //create a new sprite and add it to the scene
    QImage image(":assets/Box.png");
    int width = BOX_SPRITE_WIDTH;//image.width();
    int height = BOX_SPRITE_HEIGHT;//image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/Box.png", nullptr, this->x-(width/2), this->y-(height/2));
    
    scene->addItem(sprite);
}


/// @brief Removes box from the scene
/// @param scene 
void Box::despawn(QGraphicsScene* scene)
{
    scene->removeItem(sprite);
}

/// @brief Saves box data into string
/// @return string with box data
std::string Box::getSaveString()
{
    std::string out =   "(" +
                        std::to_string(this->x) + "," +
                        std::to_string(this->y) + 
                        ")";
    return out;
}