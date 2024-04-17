#include "Controller.hpp"
#include <iostream>

#define ROBOT_SPRITE_HEIGHT 64
#define ROBOT_SPRITE_WIDTH 64

Controller::Controller() {
}

Controller::~Controller() {

    for (Robot* robot : robots) {
        delete robot;
    }
}

void Controller::addRobot(int x, int y){
    // if(x + ROBOT_SPRITE_WIDTH/2 > this->map_width || y + ROBOT_SPRITE_HEIGHT/2 > this->map_height){
    //     std::cout << "Robot out of bounds" << std::endl;
    // }
    robots.push_back(new Robot(x, y));
}

void Controller::spawnTopmostRobot(){
    robots.back()->spawn(&scene);
}


void Controller::spawnRobots(){
     for (Robot* robot : robots) {
        robot->spawn(&scene);
    }
    // robots.clear();
}