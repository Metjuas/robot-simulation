#include "Robot.hpp"

#define SPAWN_OFFSET 0

const int DEFAULT_DETECTION_DISTANCE = 30;
const int DEFAULT_ROBOT_ROTATION_ANGLE = 60;
const std::string DEFAULT_ROBOT_NAME = "robot";

Robot::Robot(int pos_x, int pos_y)
{

    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->robot_name = DEFAULT_ROBOT_NAME;
    this->rotation_angle = 0;
    this->distance = DEFAULT_DETECTION_DISTANCE;
    this->direction = LEFT;
    this->sprite = nullptr;
    this->is_rotating = false;
    this->rotation_checker = 0;
    this->collision = false;
    this->robot_rotation = DEFAULT_ROBOT_ROTATION_ANGLE;
    this->player_go = false;
    this->player_left = false;
    this->player_right = false;
}

Robot::Robot(std::string name, int pos_x, int pos_y, int rotation, int distance, RotationDirection direction, int robot_rotation)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->robot_name = name;
    this->rotation_angle = rotation;
    this->distance = distance;
    this->direction = direction;
    this->robot_rotation = robot_rotation;
    this->sprite = nullptr;
    this->is_rotating = false;
    this->rotation_checker = 0;
    this->collision = false;
    this->player_go = false;
    this->player_left = false;
    this->player_right = false;
}

/// @brief removes robot sprite
Robot::~Robot()
{
    // if the sprite exists, delete it

    if (sprite != nullptr)
    {
        delete sprite;
    }
}
/// @brief main simulation function for the robot. It checks for collisions and moves the robot accordingly
/// @param scene 
void Robot::simulate(QGraphicsScene *scene)
{
    QList<QGraphicsItem *> items_in_front;
    QList<QGraphicsItem *> items_on_robot;
    bool out_of_bounds;
    std::tie(items_in_front, items_on_robot, out_of_bounds) = detectCollision(scene);

    if (!is_rotating && (!items_in_front.empty() || !items_on_robot.empty() || out_of_bounds))
    {
        // if there is a collision, start rotating the robot
        is_rotating = true;
        rotation_checker = robot_rotation;
    }

    if (!items_on_robot.empty())
    {
        collision = true;
    }

    if (is_rotating)
    {
        rotate();
        if (is_rotating == false && items_in_front.empty())
        {
            move();
        }
    }
    else
    {
        move();
    }
}

/// @brief function for rotating the robot
void Robot::rotate()
{
    if (sprite && rotation_checker > 0)
    {
        if (direction == RIGHT)
        {
            sprite->setRotation(sprite->rotation() + 1);
            rotation_checker--;
            if (rotation_checker == 0)
            {
                is_rotating = false;
            }
        }
        else
        {
            sprite->setRotation(sprite->rotation() - 1);
            rotation_checker--;
            if (rotation_checker == 0)
            {
                is_rotating = false;
            }
        }
    }
    // Set the point of rotation to the center of the sprite
}

/// @brief function for spawning the robot sprite
/// @param scene 
void Robot::spawn(QGraphicsScene *scene)
{
    // create a new sprite and add it to the scene
    QImage image(":assets/RobotEnemy.png");
    int width = image.width();
    int height = image.height();

    // there is a offset needed, because the sprite will spawn in the top left corner of the image
    sprite = new Sprite(":assets/RobotEnemy.png", nullptr, this->pos_x - (width / 2), this->pos_y - (height / 2));
    sprite->setTransformOriginPoint(sprite->boundingRect().width() / 2.0, sprite->boundingRect().height() / 2.0);

    scene->addItem(sprite);
        
    this->setSpriteRotation();
    this->setSpriteRotation();
}

void Robot::despawn(QGraphicsScene *scene)
{
    scene->removeItem(sprite);
}

/// @brief moves the robot sprite
void Robot::move()
{
    if (sprite)
    {
        // calculating new position based on current rotation
        double rotation = sprite->rotation() * M_PI / 180.0;

        double new_x = sprite->x() + cos(rotation);
        double new_y = sprite->y() + sin(rotation);
        this->pos_x = (int)new_x;
        this->pos_y = (int)new_y;

        sprite->setPos(new_x, new_y);
    }
}

/// @brief function for detecting collisions in front of the robot and on robot
/// @param scene 
/// @return tuple of QList<QGraphicsItem *>, QList<QGraphicsItem *>, bool - items in front of the robot, items on the robot, out of bounds
std::tuple<QList<QGraphicsItem *>, QList<QGraphicsItem *>, bool> Robot::detectCollision(QGraphicsScene *scene)
{
    qreal radius = sprite->boundingRect().width() / 2.0;
    qreal detection_distance = distance;

    // Calculate the center of the detection rectangle
    qreal center_x = sprite->pos().x() + radius + cos(sprite->rotation() * M_PI / 180.0) * (radius + detection_distance);
    qreal center_y = sprite->pos().y() + radius + sin(sprite->rotation() * M_PI / 180.0) * (radius + detection_distance);
    // Create the detection rectangle
    QRectF detection_rectangle(center_x - detection_distance / 2.0, center_y - detection_distance / 2.0, detection_distance, detection_distance);

    QList<QGraphicsItem *> items_in_front = scene->items(detection_rectangle);
    QList<QGraphicsItem *> items_on_robot = sprite->collidingItems();
    bool out_of_bounds = false;

    QRectF map_rectangle(scene->sceneRect().topLeft(), scene->sceneRect().bottomRight());

    if (!map_rectangle.contains(detection_rectangle))
    {
        out_of_bounds = true;
    }

    return std::make_tuple(items_in_front, items_on_robot, out_of_bounds);
}

/// @brief saves the robot to a string
/// @return 
std::string Robot::getSaveString()
{
    std::string robotDirection = this->direction == LEFT ? "LEFT" : "RIGHT";

    std::string out = "(" +
                      this->robot_name + "," +
                      std::to_string(this->pos_x) + "," +
                      std::to_string(this->pos_y) + "," +
                      std::to_string(this->distance) + "," +
                      std::to_string(this->rotation_angle) + "," +
                      robotDirection + "," +
                      std::to_string(this->robot_rotation) + ")";
    return out;
}

/// @brief selects the robot
void Robot::select()
{
    if (this->sprite != nullptr)
    {
        this->sprite->changeImage(":assets/RobotAlly.png");
    }
}

/// @brief unselects the robot
void Robot::unselect()
{
    if (this->sprite != nullptr)
    {
        this->sprite->changeImage(":assets/RobotEnemy.png");
    }
}

/// @brief set the robot sprite
void Robot::setSpriteRotation()
{
    if (direction == LEFT)
    {
        this->sprite->setRotation(-this->rotation_angle);
    }
    else
    {
        this->sprite->setRotation(this->rotation_angle);
    }
}

/// @brief player control function for the robot
/// @param scene 
void Robot::playerControl(QGraphicsScene *scene)
{
    if (this->player_left)
    {
        sprite->setRotation(sprite->rotation() - 1);
    }
    else if (this->player_right)
    {
        sprite->setRotation(sprite->rotation() + 1);
    }
    else if (this->player_go)
    {
        QList<QGraphicsItem *> items_in_front;
        QList<QGraphicsItem *> items_on_robot;
        bool out_of_bounds;
        std::tie(items_in_front, items_on_robot, out_of_bounds) = detectCollision(scene);

        if (!(!items_in_front.empty() || !items_on_robot.empty() || out_of_bounds))
        {
            move();
        }
    }
}