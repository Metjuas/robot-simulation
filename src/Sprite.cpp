#include "Sprite.hpp"
#include <QPixmap>
#include <QDebug>
#include <QDir>

Sprite::Sprite(const QString &filePath, QWidget *parent, unsigned int posX, unsigned int posY) : QLabel(parent)
{
    QPixmap pixmap(filePath);
    if(pixmap.isNull()) {
        // debug prints
        qDebug() << "Current directory:" << QDir::currentPath();
        qDebug() << "Image path:" << QDir::currentPath() + filePath;
    } else {
        this->setPixmap(pixmap);
        this->setGeometry(posX, posY, pixmap.width(), pixmap.height());
        this->show();
    }
}