// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#include "Sprite.hpp"
#include <iostream>


Sprite::Sprite(const QString &filePath, QGraphicsItem *parent, unsigned int posX, unsigned int posY)
    : QGraphicsPixmapItem(parent) {
    QPixmap pixmap(filePath);
    if(pixmap.isNull()) {
        // debug prints
        qDebug() << "Current directory:" << QDir::currentPath();
        qDebug() << "Image path:" << QDir::currentPath() + filePath;
    } else {
        setPixmap(pixmap);
        setPos(posX, posY);
    }
}

void Sprite::changeImage(const QString &filePath)
{
    QPixmap pixmap(filePath);
    if(pixmap.isNull()) {
        // debug prints
        qDebug() << "Current directory:" << QDir::currentPath();
        qDebug() << "Image path:" << QDir::currentPath() + filePath;
    } else {
        setPixmap(pixmap);
    }
}