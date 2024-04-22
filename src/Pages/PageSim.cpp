#include "PageSim.hpp"
#include <iostream>
#define TickRate 2

PageSim::PageSim(QStackedWidget *stackedWidget, QWidget *parent, Controller *controller) : QWidget(parent), m_stackedWidget(stackedWidget), controller(controller){
    this->controller = controller;
    view = new CustomGraphicsView(&controller->scene, nullptr);
    view->setRenderHint(QPainter::Antialiasing);
    
    QPushButton *pause_button = new QPushButton("Pause simulation", this);
    pause_button->setFixedHeight(50);
    QPushButton *menu_button = new QPushButton("Menu", this);
    menu_button->setFixedHeight(50);
    QPushButton *go_button = new QPushButton("Go", this);
    go_button->setCheckable(true);
    QPushButton *left_button = new QPushButton("<-", this);
    QPushButton *right_button = new QPushButton("->", this);
    //button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //pause button Click
    connect(menu_button, &QPushButton::clicked, [=]() {
        parent->resize(300,500);
        controller->clearAll();
        stackedWidget->setCurrentIndex(0);
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
    connect(go_button, &QPushButton::toggled, [this, go_button, controller](bool checked) {
        if(controller->getSelectedRobot() != nullptr)
        {
            if(checked)
            {
                go_button->setText(QString::fromStdString("Stop"));
                controller->getSelectedRobot()->playerGo = true;
            }
            else
            {
                go_button->setText(QString::fromStdString("Go"));
                controller->getSelectedRobot()->playerGo = false;
            }
        }
    });

    //left button event
    connect(left_button, &QPushButton::pressed, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->playerLeft = true;
        }
    });
    connect(left_button, &QPushButton::released, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->playerLeft = false;
        }
    });


    //right button event
    connect(right_button, &QPushButton::pressed, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->playerRight = true;
        }
    });
    connect(right_button, &QPushButton::released, [=]() {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->playerRight = false;
        }
    });


    //setLayout
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(pause_button, 0, 0, 2, 2);
    gridLayout->addWidget(menu_button, 0, 10, 2, 2);
    gridLayout->addWidget(go_button, 0, 4, 1, 2);
    gridLayout->addWidget(left_button, 1, 4);
    gridLayout->addWidget(right_button, 1, 5);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(view);
    vLayout->addLayout(gridLayout);

    

    this->setLayout(vLayout);
    view->setMode(CustomGraphicsView::RecordClicks);

}

void PageSim::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // Start the simulation
    controller->startSimulation();
}

PageSim::~PageSim() {

}

bool PageSim::robotSelectGUI(bool toggle)
{

}

void PageSim::handleMouseClick(int x, int y){
    int ret = controller->selectRobot(x-32,y-32);
    if(ret == 1)
    {
        robotSelectGUI(true);
    }
    else if(ret == 2)
    {
        robotSelectGUI(false);
    }
}