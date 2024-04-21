#include "Controller.hpp"
#include <iostream>

#define ROBOT_SPRITE_HEIGHT 64
#define ROBOT_SPRITE_WIDTH 64

Controller::Controller() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Controller::simulateAll);
}

Controller::~Controller() {

    for (Robot* robot : robots) {
        delete robot;
    }
}

void Controller::addRobot(int x, int y){
    //this might need some changes
    QRect newRobotRect(x, y, 50, 50); 

    for (Robot* robot : robots) {
        QRect existingRobotRect(robot->getPosX(), robot->getPosY(), 50, 50); 

        if (newRobotRect.intersects(existingRobotRect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    robots.push_back(new Robot(x, y));
}

void Controller::startSimulation(){
    timer->start(20);
    robots.back()->simulate(&scene);
}
void Controller::stopSimulation(){
    timer->stop();

}

void Controller::simulateAll() {
    // for (Robot* robot : robots) {
    //     robot->simulate(&scene);
    // }
    robots.back()->simulate(&scene);
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