#pragma once

class Robot {
    public:
        Robot(int posX, int posY);
        void spawn();
        void move();
    private:
        int posX;
        int posY;
};
            