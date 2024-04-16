#pragma once

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QDir>
#include <QPixmap>

class Sprite : public QGraphicsPixmapItem {
public:
    //filepath, parent, position x, position y
    ~Sprite();
    explicit Sprite(const QString &filePath, QGraphicsItem *parent = nullptr, unsigned int posX = 0, unsigned int posY = 0);
};