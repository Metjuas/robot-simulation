#include "Sprite.hpp"
#include <QPixmap>
#include <QDebug>
#include <QDir>

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