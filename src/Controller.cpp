#include "Controller.hpp"

const int ROBOT_SPRITE_HEIGHT = 64;
const int ROBOT_SPRITE_WIDTH = 64;
const int ROBOT_SPRITE_OFFSET = 32;

const int ROBOT_HITBOX = 50;

const int BOX_SPRITE_HEIGHT = 64;
const int BOX_SPRITE_WIDTH = 64;
const int BOX_HITBOX = 50;


Controller::Controller() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Controller::simulateAll);
    this->map_height = 0;
    this->map_width = 0;
    this->selected_robot = nullptr;
}

Controller::~Controller() {

    for (Robot* robot : robots) {
        delete robot;
    }
}

void Controller::clearAll(){
    for (Robot* robot : robots) {
        delete robot;
    }
    for (Box* box : boxes) {
        delete box;
    }
    robots.clear();
    boxes.clear();
    this->selected_robot = nullptr;
    this->scene.clear();
    this->timer->stop();
}


bool Controller::addRobot(int x, int y){
    //this might need some changes
    QRect new_robot_rect(x, y, ROBOT_HITBOX, ROBOT_HITBOX); 

    for (Robot* robot : robots) {
        QRect existing_robot_rect(robot->getPosX(), robot->getPosY(), ROBOT_HITBOX, ROBOT_HITBOX); 

        if (new_robot_rect.intersects(existing_robot_rect)) {
            return false;
        }
    }

    for (Box* box : boxes) {
        if (box != nullptr) {
            QRect existing_box_rect(box->getPosX(), box->getPosY(), BOX_HITBOX, BOX_HITBOX); 

            if (new_robot_rect.intersects(existing_box_rect)) {
                return false;
            }
        }
    }

    // The new robot does not overlap with any existing robots or boxes, so add it
    robots.push_back(new Robot(x, y));
    return true;
}

void Controller::startSimulation(){
    timer->start(10);
    for (Robot* robot : robots) {
        robot->simulate(&scene);
    }
}

void Controller::stopSimulation(){
    timer->stop();
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

    std::string robot_name = command[0];
    int robot_x = std::stoi(command[1]);
    int robot_y = std::stoi(command[2]);
    int robot_distance = std::stoi(command[3]);
    int robot_rotation = std::stoi(command[4]);
    RotationDirection robot_direction = strcmp(command[5].c_str(),"LEFT")? LEFT : RIGHT;

    //this might need some changes
    QRect new_robot_rect(robot_x, robot_y, ROBOT_HITBOX, ROBOT_HITBOX); 

    for (Robot* robot : this->robots) {
        QRect existing_robot_rect(robot->getPosX(), robot->getPosY(), ROBOT_HITBOX, ROBOT_HITBOX); 

        if (new_robot_rect.intersects(existing_robot_rect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    this->robots.push_back(new Robot(robot_name, robot_x, robot_y, robot_rotation, robot_distance, robot_direction));
}



void Controller::simulateAll() {
    for (Robot* robot : robots) {
        if(this->selected_robot != robot)
        {
            robot->simulate(&scene);
        }
        else
        {
            robot->playerControl(&scene);
        }
    }
    // robots.back()->simulate(&scene);
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

bool Controller::addBox(int x, int y){
    //this might need some changes
      QRect new_box_rect(x, y, BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 

    for (Box* box : boxes) {
        QRect existing_box_rect(box->getPosX(), box->getPosY(), BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 

        if (new_box_rect.intersects(existing_box_rect)) {
            return false;
        }
    }

    for (Robot* robot : robots) {
        QRect existing_robot_rect(robot->getPosX(), robot->getPosY(), ROBOT_SPRITE_HEIGHT, ROBOT_SPRITE_WIDTH); 

        if (new_box_rect.intersects(existing_robot_rect)) {
            return false;
        }
    }

    // The new box does not overlap with any existing boxes or robots, so add it
    boxes.push_back(new Box(x, y));
    return true;
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

    int box_x = std::stoi(command[0]);
    int box_y = std::stoi(command[1]);

    //this might need some changes
    QRect new_box_rect(box_x, box_y, BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 

    for (Box* box : boxes) {
        QRect existing_box_rect(box->getPosX(), box->getPosY(), BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 

        if (new_box_rect.intersects(existing_box_rect)) {
            return;
        }
    }
    // The new robot does not overlap with any existing robots, so add it
    boxes.push_back(new Box(box_x, box_y));
}

void Controller::spawnTopmostBox(){
    boxes.back()->spawn(&scene);
}

void Controller::removeItem(int x, int y)
{
    //Remove box
    QRect new_box_rect(x, y, BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 
    for (Box* box : boxes) {
        QRect existing_box_rect(box->getPosX(), box->getPosY(), BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH); 

        if (new_box_rect.intersects(existing_box_rect)) {
            boxes.erase(std::remove(boxes.begin(), boxes.end(), box), boxes.end());
            box->despawn(&scene);
            return;
        }
    }

    //Remove robot
    QRect new_robot_rect(x, y, ROBOT_HITBOX, ROBOT_HITBOX); 

    for (Robot* robot : robots) {
        QRect existing_robot_rect(robot->getPosX(), robot->getPosY(), ROBOT_HITBOX, ROBOT_HITBOX); 

        if (new_robot_rect.intersects(existing_robot_rect)) {
            if(robot == this->selected_robot)this->selected_robot=nullptr;
            robots.erase(std::remove(robots.begin(), robots.end(), robot), robots.end());
            robot->despawn(&scene);
            return;
        }
    }
}

int Controller::saveMap(std::string map_name)
{
    if(map_name.size() == 0)return 1;
    if(std::filesystem::exists("maps/" + map_name + ".map"))return 2;
    //create map directory if not exists
    if (!std::filesystem::is_directory("maps") || !std::filesystem::exists("maps"))
    {
        std::filesystem::create_directory("maps");
    }

    //create map file
    std::ofstream map_file("maps/" + map_name + ".map");

    //insert data to map file
    map_file << "(" + std::to_string(this->map_width) + "," + std::to_string(this->map_height) + ")";

    map_file << "\n";

    for (Robot* robot : robots) {
        map_file << robot->getSaveString();
    }

    map_file << "\n";

    for (Box* box : boxes) {
        map_file << box->getSaveString();
    }

    map_file << "\n";

    return 0;
}

int Controller::loadMap(std::string file_path)
{
    //clear map
    this->robots.clear();
    this->boxes.clear();

    //open file
    std::ifstream map_file(file_path);
    if(!map_file.is_open())return 1;
    std::string item;
    
    //get map size
    item = getFileObject(map_file);
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
    if(map_file.get() != '\n')return 2;

    //get robots
    while(map_file.peek() != '\n')
    {
        item = getFileObject(map_file);
        if(strcmp(item.c_str(), "") == 0)return 2;
        if(countChars(item, ',') != 5)return 2;

        addRobot(item);
        spawnTopmostRobot();
    }
    if(map_file.get() != '\n')return 2;

    //get boxes
    while(map_file.peek() != '\n')
    {
        item = getFileObject(map_file);
        if(strcmp(item.c_str(), "") == 0)return 2;
        if(countChars(item, ',') != 1)return 2;

        addBox(item);
        spawnTopmostBox();
    }
    if(map_file.get() != '\n')return 2;

    this->selected_robot = nullptr;
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
    Robot *newselected_robot = nullptr;
    for (Robot* robot : this->robots) {
        if(robot == nullptr){
            return 2;
        }

        QRect existing_robot_rect(robot->getPosX()-ROBOT_SPRITE_OFFSET, robot->getPosY()-ROBOT_SPRITE_OFFSET, ROBOT_SPRITE_HEIGHT, ROBOT_SPRITE_WIDTH);
        if(existing_robot_rect.contains(x,y))
        {
            newselected_robot = robot;
        }
    }

    //no robot was selected
    if(newselected_robot == nullptr)return 0;

    //unselect if selected same robot
    if(newselected_robot == this->selected_robot)
    {
        unselectRobot();
        return 2;
    }

    //select robot
    unselectRobot();

    this->selected_robot = newselected_robot;
    selected_robot->select();
    return 1;

}

void Controller::unselectRobot()
{
    if(this->selected_robot != nullptr)
    {
        this->selected_robot->unselect();
        this->selected_robot = nullptr;
    }
}