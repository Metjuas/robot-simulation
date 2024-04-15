#pragma once

#include <vector>
#include "Robot.hpp"

class Controller {
    public:
        Controller(){}; // Default constructor
        ~Controller(){}; // Default destructor
        int map_height;
        int map_width;

    private:
        std::vector<Robot> robots;
};

