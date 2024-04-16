#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
    //fill in the robots vector with the robots
    robots.push_back(new Robot(0,0));
    robots.push_back(new Robot(200,200));
    // robots.push_back(new Robot(500,300));
}

Controller::~Controller() {
    std::cerr << "Controller destructor start" << std::endl;

    for (Robot* robot : robots) {
        delete robot;
    }
    std::cerr << "Controller destructor end" << std::endl;
}

void Controller::AddRobot(int x, int y){
    robots.push_back(new Robot(x, y));
}

void Controller::spawnRobots(){
     for (Robot* robot : robots) {
        robot->spawn(&scene);
    }
    // robots.clear();
}