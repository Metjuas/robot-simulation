#pragma once

#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDir>

class Sprite : public QLabel {
    Q_OBJECT

public:
    //filepath, parent, position x, position y
    explicit Sprite(const QString &filePath, QWidget *parent, unsigned int posX, unsigned int posY);
};