// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#pragma once

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QDir>
#include <QPixmap>

class Sprite : public QGraphicsPixmapItem {
public:
    //filepath, parent, position x, position y
    explicit Sprite(const QString &filePath, QGraphicsItem *parent = nullptr, unsigned int posX = 0, unsigned int posY = 0);
    void changeImage(const QString &filePath);
};