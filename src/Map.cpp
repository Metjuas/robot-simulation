// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0



#include "Map.hpp"

#define block_size_ratio 10

// constructor for the Map class, paints the background of the scene with a texture


/// @brief creates map object, sets the background texture of the scene
/// @param controller 
/// @param parent 
Map::Map(Controller* controller, QWidget *parent) : parent(parent), controller(controller) {
    QPixmap texture(":/assets/Iron.png");
    if (texture.isNull()) {
        qDebug() << "Failed to load texture";
    } else {
        texture = texture.scaled(texture.width() / block_size_ratio, texture.height() / block_size_ratio);  
        controller->scene.setBackgroundBrush(texture);
    }
}

