#include "Robot.hpp"


#define SPAWN_OFFSET 0

Robot::Robot(int posX, int posY) {
    
    this->posX = posX;
    this->posY = posY;
    this->robotName = "robot";
    this->rotationAngle = 0;
    this->distance = 50;
    this->direction = LEFT;
}

Robot::Robot(std::string name, int posX, int posY, int rotation, int distance, RotationDirection direction)
{
    this->posX = posX;
    this->posY = posY;
    this->robotName = name;
    this->rotationAngle = rotation;
    this->distance = distance;
    this->direction = direction;
}

Robot::~Robot() {
    //if the sprite exists, delete it

    if (sprite != nullptr) {
        delete sprite;
    }
}  

void Robot::simulate(QGraphicsScene *scene) {
    QList<QGraphicsItem*> itemsInFront;
    QList<QGraphicsItem*> itemsOnRobot;
    bool outOfBounds;
    std::tie(itemsInFront, itemsOnRobot, outOfBounds) = detectCollision(scene);

    if(!is_rotating && (!itemsInFront.empty() || !itemsOnRobot.empty() || outOfBounds)){
    //if there is a collision, start rotating the robot
        is_rotating = true;
        rotation_checker = 15;
    }   

    if(!itemsOnRobot.empty()){
        collision = true;
    }

    if(is_rotating){
        rotate();
        if(is_rotating == false && itemsInFront.empty()){
            move();
        }
    } else {
        move();
    }
}


void Robot::rotate() {
    if (sprite && rotation_checker > 0) {
        // Set the point of rotation to the center of the sprite
        sprite->setRotation(sprite->rotation() + 1);
        rotation_checker--;
        if (rotation_checker == 0) {
            is_rotating = false;
        }
    }
}

void Robot::spawn(QGraphicsScene* scene) {
    //create a new sprite and add it to the scene
    QImage image(":assets/RobotEnemy.png");
    int width = image.width();
    int height = image.height();

    //there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/RobotEnemy.png", nullptr, this->posX-(width/2), this->posY-(height/2));
    sprite->setTransformOriginPoint(sprite->boundingRect().width() / 2.0, sprite->boundingRect().height() / 2.0);
    
    scene->addItem(sprite);
}

void Robot::despawn(QGraphicsScene* scene)
{
    scene->removeItem(sprite);
}

void Robot::move() {
    if (sprite) { 
        //calculating new position based on current rotation
        double rotation = sprite->rotation() * M_PI / 180.0;

        double newX = sprite->x() + cos(rotation);
        double newY = sprite->y() + sin(rotation);
        //std::cout << "x: " << (int)newX << " y: " << (int)newY << "\n";
        this->posX = (int)newX;
        this->posY = (int)newY;

        sprite->setPos(newX, newY);
    }
}



std::tuple<QList<QGraphicsItem*>, QList<QGraphicsItem*>, bool> Robot::detectCollision(QGraphicsScene* scene) {
    qreal radius = sprite->boundingRect().width() / 2.0;
    qreal detectionDistance = 25;

    // Calculate the center of the detection rectangle
    qreal centerX = sprite->pos().x() + radius + cos(sprite->rotation() * M_PI / 180.0) * (radius + detectionDistance);
    qreal centerY = sprite->pos().y() + radius + sin(sprite->rotation() * M_PI / 180.0) * (radius + detectionDistance);
    // Create the detection rectangle
    QRectF detectionRect(centerX - detectionDistance / 2.0, centerY - detectionDistance / 2.0, detectionDistance, detectionDistance);

    QList<QGraphicsItem*> itemsInFront = scene->items(detectionRect);
    QList<QGraphicsItem*> itemsOnRobot = sprite->collidingItems();
    bool outOfBounds = false;

    QRectF map_rectangle(scene->sceneRect().topLeft(),scene->sceneRect().bottomRight());

    if(!map_rectangle.contains(detectionRect)){
        outOfBounds = true;
    }
    //itemsOnRobot.removeAll(sprite);

    return std::make_tuple(itemsInFront, itemsOnRobot, outOfBounds);
}

std::string Robot::getSaveString()
{
    std::string robotDirection = this->direction==LEFT ? "LEFT" : "RIGHT";

    std::string out =   "(" + 
                        this->robotName + "," +
                        std::to_string(this->posX) + "," +
                        std::to_string(this->posY) + "," +
                        std::to_string(this->distance) + "," +
                        std::to_string(this->rotationAngle) + "," +
                        robotDirection
                        + ")";
    return out;
}


void Robot::select()
{
    if(this->sprite != nullptr)
    {
        this->sprite->changeImage(":assets/RobotAlly.png");
    }
}

void Robot::unselect()
{
    if(this->sprite != nullptr)
    {
        this->sprite->changeImage(":assets/RobotEnemy.png");
    }
}

void Robot::setSpriteRotation()
{
    if(direction == LEFT)
    {
        this->sprite->setRotation(-this->rotationAngle);
    }
    else
    {
        this->sprite->setRotation(this->rotationAngle);
    }
}

void Robot::playerControl(QGraphicsScene *scene)
{
    if(this->playerLeft)
    {
        sprite->setRotation(sprite->rotation() - 1);
    }
    else if(this->playerRight)
    {
        sprite->setRotation(sprite->rotation() + 1);
    }
    else if(this->playerGo)
    {
        QList<QGraphicsItem*> itemsInFront;
        QList<QGraphicsItem*> itemsOnRobot;
        bool outOfBounds;
        std::tie(itemsInFront, itemsOnRobot, outOfBounds) = detectCollision(scene);

        if(!(!itemsInFront.empty() || !itemsOnRobot.empty() || outOfBounds)){
            move();
        }
    }
}