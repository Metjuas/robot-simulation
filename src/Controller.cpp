#include "Controller.hpp"

Controller::Controller() {
    //fill in the robots vector with the robots
    robots.push_back(new Robot(100,100));
    robots.push_back(new Robot(200,200));
    robots.push_back(new Robot(500,300));
}

Controller::~Controller() {
    for (Robot* robot : robots) {
        delete robot;
    }
}

void Controller::spawnRobots(){
     for (Robot* robot : robots) {
        robot->spawn(&scene);
    }
    robots.clear();
}