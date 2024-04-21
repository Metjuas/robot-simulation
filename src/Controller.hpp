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

class Controller : public QObject{
    public:
        Controller(); // Default constructor
        ~Controller(); // Default destructor
        void spawnRobots();
        int map_height;
        int map_width;
        QGraphicsScene scene;
        void addRobot(int x, int y);
        void addRobot(std::string input);
        void spawnTopmostRobot();
        void startSimulation();
        void stopSimulation();
        QTimer *timer;
        void addBox(int x, int y);
        void addBox(std::string input);
        void spawnTopmostBox();
        void removeItem(int x, int y);
        int saveMap(std::string mapName);
        int loadMap(std::string filePath);
        Robot *getSelectedRobot() { return this->selectedRobot; }

        int selectRobot(int x, int y);
        void unselectRobot();

    public slots:
        void simulateAll();
        
    private:
        std::string getFileObject(std::ifstream &file);
        int countChars(std::string input, char chr);
        std::vector<Robot*> robots;
        std::vector<Box*> boxes;
        Robot *selectedRobot;
};

