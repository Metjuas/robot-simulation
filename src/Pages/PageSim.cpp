#include "PageSim.hpp"


const int ROBOT_SPRITE_OFFSET = 32;

/// @brief Creates simulation page, adds layout and buttons
/// @param stacked_widget widget for swapping pages
/// @param parent main window - parent
/// @param controller controller for passing data
PageSim::PageSim(QStackedWidget *stacked_widget, QWidget *parent, Controller *controller) : QWidget(parent), stacked_widget(stacked_widget), controller(controller){
    this->controller = controller;
    view = new CustomGraphicsView(&controller->scene, nullptr);
    view->setRenderHint(QPainter::Antialiasing);
    
    QPushButton *pause_button = new QPushButton("Pause simulation", this);
    pause_button->setFixedHeight(50);
    QPushButton *menu_button = new QPushButton("Menu", this);
    menu_button->setFixedHeight(50);
    go_button = new QPushButton("Go", this);
    go_button->setCheckable(true);
    left_button = new QPushButton("<-", this);
    right_button = new QPushButton("->", this);

    //pause button Click
    connect(menu_button, &QPushButton::clicked, [=]() {
        stacked_widget->setCurrentIndex(0);
    });

    //menu button Click
    connect(pause_button, &QPushButton::clicked, [=]() {

        if(controller->timer->isActive()){
            controller->stopSimulation();
            pause_button->setText("Resume");
        }
        else{
            controller->startSimulation();
            pause_button->setText("Pause simulation");
        }
    });

    QObject::connect(view, &CustomGraphicsView::mouseClick, this, &PageSim::handleMouseClick);

    //Robot control buttons
    //go button Click
    connect(go_button, &QPushButton::toggled, [this, controller](bool checked) {
        if(controller->getSelectedRobot() != nullptr)
        {
            if(checked)
            {
                go_button->setText(QString::fromStdString("Stop"));
                controller->getSelectedRobot()->player_go = true;
            }
            else
            {
                go_button->setText(QString::fromStdString("Go"));
                controller->getSelectedRobot()->player_go = false;
            }
        }
    });

    //left button event
    connect(left_button, &QPushButton::pressed, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->player_left = true;
        }
    });
    connect(left_button, &QPushButton::released, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->player_left = false;
        }
    });

    //right button event
    connect(right_button, &QPushButton::pressed, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->player_right = true;
        }
    });
    connect(right_button, &QPushButton::released, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->player_right = false;
        }
    });

    //setLayout
    grid_layout = new QGridLayout();
    grid_layout->columnMinimumWidth(10);
    grid_layout->addWidget(pause_button, 0, 0, 2, 2);
    grid_layout->addWidget(menu_button, 0, 10, 2, 2);
    grid_layout->addWidget(go_button, 0, 4, 1, 2);
    grid_layout->addWidget(left_button, 1, 4);
    grid_layout->addWidget(right_button, 1, 5);

    v_layout = new QVBoxLayout();

    this->setLayout(v_layout);
    view->setMode(CustomGraphicsView::RecordClicks);
    robotSelectGUI(false);
}

/// @brief showEvent for simulation page, handles 
/// @param event 
void PageSim::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    view->setFixedSize(controller->map_width, controller->map_height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Start the simulation
    controller->startSimulation();

    v_layout->addWidget(view);
    v_layout->addLayout(grid_layout);
}

/// @brief hideEvent for simulation page
void PageSim::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);

    controller->stopSimulation();
    v_layout->removeWidget(view);
    v_layout->removeItem(grid_layout);
}



/// @brief handles robot selection 
/// @param toggle 
void PageSim::robotSelectGUI(bool toggle)
{
    if(this->controller->getSelectedRobot() != nullptr)
    {
        go_button->setText(QString::fromStdString("Go"));
    }
    go_button->setChecked(false);

    if(toggle)
    {
        go_button->setEnabled(true);
        left_button->setEnabled(true);
        right_button->setEnabled(true);
    }
    else
    {
        go_button->setEnabled(false);
        left_button->setEnabled(false);
        right_button->setEnabled(false);
    }
}

/// @brief handles mouse click events
/// @param x position on x axis
/// @param y position on y axis
void PageSim::handleMouseClick(int x, int y){
    int ret = controller->selectRobot(x-ROBOT_SPRITE_OFFSET,y-ROBOT_SPRITE_OFFSET);
    if(ret == 1)
    {
        robotSelectGUI(true);
    }
    else if(ret == 2)
    {
        robotSelectGUI(false);
    }
}