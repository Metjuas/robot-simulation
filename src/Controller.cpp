#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
}

Controller::~Controller() {

    for (Robot* robot : robots) {
        delete robot;
    }
}

void Controller::addRobot(int x, int y){
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