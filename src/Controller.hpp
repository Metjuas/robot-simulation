#pragma once

#include <vector>
#include "Robot.hpp"
#include <QGraphicsView>
#include <QTimer>

class Controller : public QObject{
    public:
        Controller(); // Default constructor
        ~Controller(); // Default destructor
        void spawnRobots();
        int map_height;
        int map_width;
        QGraphicsScene scene;
        void addRobot(int x, int y);
        void spawnTopmostRobot();
        void startSimulation();
        void stopSimulation();
        QTimer *timer;

    public slots:
        void simulateAll();

    private:
        std::vector<Robot*> robots;
};

