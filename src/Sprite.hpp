#pragma once

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QDir>

class Sprite : public QGraphicsPixmapItem {
public:
    //filepath, parent, position x, position y
    explicit Sprite(const QString &filePath, QGraphicsItem *parent = nullptr, unsigned int posX = 0, unsigned int posY = 0);
};