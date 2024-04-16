#pragma once

#include <vector>
#include "Robot.hpp"
#include <QGraphicsView>


class Controller {
    public:
        Controller(); // Default constructor
        ~Controller(); // Default destructor
        void spawnRobots();
        int map_height;
        int map_width;
        QGraphicsScene scene;
        void addRobot(int x, int y);
        void spawnTopmostRobot();

    private:
        std::vector<Robot*> robots;
};

