#pragma once

#include <vector>
#include "Robot.hpp"
#include "Box.hpp"
#include <QGraphicsView>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>


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
        void addBox(int x, int y);
        void spawnTopmostBox();
        void removeItem(int x, int y);
        int saveMap(std::string mapName);

    private:
        std::vector<Robot*> robots;
        std::vector<Box*> boxes;
};

