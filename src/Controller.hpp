// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#pragma once

#include <vector>
#include "Robot.hpp"
#include "Box.hpp"
#include <QGraphicsView>
#include <QTimer>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <QRectF>

class Controller : public QObject{
    public:
        Controller(); // Default constructor
        ~Controller(); // Default destructor
        void spawnRobots();
        int map_height;
        int map_width;
        QGraphicsScene scene;
        QRectF map_rectangle;
        bool addRobot(int x, int y);
        void addRobot(std::string input);
        void spawnTopmostRobot();
        void startSimulation();
        void stopSimulation();
        QTimer *timer;
        bool addBox(int x, int y);
        void addBox(std::string input);
        void spawnTopmostBox();
        void removeItem(int x, int y);
        int saveMap(std::string map_name);
        int loadMap(std::string filePath);
        Robot *getSelectedRobot() { return this->selected_robot; }
        bool getSimulated() {return this->simulated; }
        void setSimulated(bool sim) {this->simulated = sim; }

        int selectRobot(int x, int y);
        void unselectRobot();

        void clearAll();

    public slots:
        void simulateAll();
        
    private:
        std::string getFileObject(std::ifstream &file);
        int countChars(std::string input, char chr);
        std::vector<Robot*> robots;
        std::vector<Box*> boxes;
        Robot *selected_robot;
        bool simulated;
};

