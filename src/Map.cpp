

#include "Map.hpp"

#define block_size_ratio 10

Map::Map(Controller* controller, QWidget *parent) : m_parent(parent), m_controller(controller) {
    QPixmap texture(":/assets/Iron.png");
    if (texture.isNull()) {
        qDebug() << "Failed to load texture";
    } else {
        texture = texture.scaled(texture.width() / block_size_ratio, texture.height() / block_size_ratio);  
        m_controller->scene.setBackgroundBrush(texture);
    }
}

Map::~Map() {
}