#pragma once

#include "Sprite.hpp"

class Robot {
    public:
        Robot(int posX, int posY);
        void spawn(QWidget *parent);
        void move();
        void rotate();
        
    private:
        int posX;
        int posY;
        Sprite *sprite;
};
            