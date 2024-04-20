#include "Controller.hpp"
#include <iostream>

#define ROBOT_SPRITE_HEIGHT 64
#define ROBOT_SPRITE_WIDTH 64

Controller::Controller() {
    this->map_height = 0;
    this->map_width = 0;
    this->selectedRobot = nullptr;
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

void Controller::addRobot(std::string input)
{
    std::vector<std::string> command;
    int start = 0;
    int end = 0;
    while ((start = (int)input.find_first_not_of(',', end)) != (int)std::string::npos) {
        end = input.find(',', start);
        command.push_back(input.substr(start, end - start));
    }

    std::string robotName = command[0];
    int robotX = std::stoi(command[1]);
    int robotY = std::stoi(command[2]);
    int robotDistance = std::stoi(command[3]);
    int robotRotation = std::stoi(command[4]);
    RotationDirection robotDirection = strcmp(command[5].c_str(),"LEFT")? LEFT : RIGHT;

    //this might need some changes
    QRect newRobotRect(robotX, robotY, 50, 50); 

    for (Robot* robot : this->robots) {
        QRect existingRobotRect(robot->getPosX(), robot->getPosY(), 50, 50); 

        if (newRobotRect.intersects(existingRobotRect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    this->robots.push_back(new Robot(robotName, robotX, robotY, robotRotation, robotDistance, robotDirection));
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

void Controller::addBox(int x, int y){
    //this might need some changes
    QRect newBoxRect(x, y, 64, 64); 

    for (Box* box : boxes) {
        QRect existingBoxRect(box->getPosX(), box->getPosY(), 64, 64); 

        if (newBoxRect.intersects(existingBoxRect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    boxes.push_back(new Box(x, y));
}

void Controller::addBox(std::string input)
{
    std::vector<std::string> command;
    int start = 0;
    int end = 0;
    while ((start = (int)input.find_first_not_of(',', end)) != (int)std::string::npos) {
        end = input.find(',', start);
        command.push_back(input.substr(start, end - start));
    }

    int boxX = std::stoi(command[0]);
    int boxY = std::stoi(command[1]);

    //this might need some changes
    QRect newBoxRect(boxX, boxY, 64, 64); 

    for (Box* box : boxes) {
        QRect existingBoxRect(box->getPosX(), box->getPosY(), 64, 64); 

        if (newBoxRect.intersects(existingBoxRect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    boxes.push_back(new Box(boxX, boxY));
}

void Controller::spawnTopmostBox(){
    boxes.back()->spawn(&scene);
}

void Controller::removeItem(int x, int y)
{
    //Remove box
    QRect newBoxRect(x, y, 64, 64); 
    for (Box* box : boxes) {
        QRect existingBoxRect(box->getPosX(), box->getPosY(), 64, 64); 

        if (newBoxRect.intersects(existingBoxRect)) {
            boxes.erase(std::remove(boxes.begin(), boxes.end(), box), boxes.end());
            box->despawn(&scene);
            return;
        }
    }

    //Remove robot
    QRect newRobotRect(x, y, 50, 50); 

    for (Robot* robot : robots) {
        QRect existingRobotRect(robot->getPosX(), robot->getPosY(), 50, 50); 

        if (newRobotRect.intersects(existingRobotRect)) {
            if(robot == this->selectedRobot)this->selectedRobot=nullptr;
            robots.erase(std::remove(robots.begin(), robots.end(), robot), robots.end());
            robot->despawn(&scene);
            return;
        }
    }
}

int Controller::saveMap(std::string mapName)
{
    if(mapName.size() == 0)return 1;
    if(std::filesystem::exists("maps/" + mapName + ".map"))return 2;
    //create map directory if not exists
    if (!std::filesystem::is_directory("maps") || !std::filesystem::exists("maps"))
    {
        std::filesystem::create_directory("maps");
    }

    //create map file
    std::ofstream mapFile("maps/" + mapName + ".map");

    //insert data to map file
    mapFile << "(" + std::to_string(this->map_width) + "," + std::to_string(this->map_height) + ")";

    mapFile << "\n";

    for (Robot* robot : robots) {
        mapFile << robot->getSaveString();
    }

    mapFile << "\n";

    for (Box* box : boxes) {
        mapFile << box->getSaveString();
    }

    mapFile << "\n";

    return 0;
}

int Controller::loadMap(std::string filePath)
{
    //clear map
    this->robots.clear();
    this->boxes.clear();

    //open file
    std::ifstream mapFile(filePath);
    if(!mapFile.is_open())return 1;
    std::string item;
    
    //get map size
    item = getFileObject(mapFile);
    if(strcmp(item.c_str(), "") == 0)return 2;
    if(countChars(item, ',') != 1)return 2;

    std::vector<std::string> command;
    int start = 0;
    int end = 0;
    while ((start = (int)item.find_first_not_of(',', end)) != (int)std::string::npos) {
        end = item.find(',', start);
        command.push_back(item.substr(start, end - start));
    }

    this->map_width = std::stoi(command[0]);
    this->map_height = std::stoi(command[1]);
    if(mapFile.get() != '\n')return 2;

    //get robots
    while(mapFile.peek() != '\n')
    {
        item = getFileObject(mapFile);
        if(strcmp(item.c_str(), "") == 0)return 2;
        if(countChars(item, ',') != 5)return 2;

        addRobot(item);
        spawnTopmostRobot();
    }
    if(mapFile.get() != '\n')return 2;

    //get boxes
    while(mapFile.peek() != '\n')
    {
        item = getFileObject(mapFile);
        if(strcmp(item.c_str(), "") == 0)return 2;
        if(countChars(item, ',') != 1)return 2;

        addBox(item);
        spawnTopmostBox();
    }
    if(mapFile.get() != '\n')return 2;

    this->selectedRobot = nullptr;
    return 0;
}

std::string Controller::getFileObject(std::ifstream &file)
{
    std::string out = "";
    if(file.get() != '(')return out;

    char mychar;
    while(file)
    {
        mychar = file.get();
        if(mychar == ')')break;
        out += mychar;
    }
    if(mychar != ')')return "";
    return out;
}

int Controller::countChars(std::string input, char chr)
{
    int cnt = 0;
    for(int i = 0;i< (int)input.size();i++)
    {
        if(input[i] == chr)cnt++;
    }
    return cnt;
}

int Controller::selectRobot(int x, int y)
{
    //check if clicked on robot 
    Robot *newselectedRobot = nullptr;
    for (Robot* robot : this->robots) {
        QRect existingRobotRect(robot->getPosX()-32, robot->getPosY()-32, 64, 64);
        if(existingRobotRect.contains(x,y))
        {
            newselectedRobot = robot;
        }
    }

    //no robot was selected
    if(newselectedRobot == nullptr)return 0;

    //unselect if selected same robot
    if(newselectedRobot == this->selectedRobot)
    {
        unselectRobot();
        return 2;
    }

    //select robot
    unselectRobot();

    this->selectedRobot = newselectedRobot;
    selectedRobot->select();
    return 1;

}

void Controller::unselectRobot()
{
    if(this->selectedRobot != nullptr)
    {
        this->selectedRobot->unselect();
        this->selectedRobot = nullptr;
    }
}