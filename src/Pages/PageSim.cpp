#include "PageSim.hpp"
#include <iostream>
#define TickRate 2

PageSim::PageSim(QWidget *parent, Controller *controller) : QWidget(parent){

    // view.setRenderHint(QPainter::Antialiasing);
    this->controller = controller;
    view = new QGraphicsView(&controller->scene, nullptr);
    
    QPushButton *pause_button = new QPushButton("Pause simulation", this);
    pause_button->setFixedHeight(50);
    QPushButton *menu_button = new QPushButton("Menu", this);
    menu_button->setFixedHeight(50);
    QPushButton *go_button = new QPushButton("Go/Stop", this);
    QPushButton *left_button = new QPushButton("<-", this);
    QPushButton *right_button = new QPushButton("->", this);
    //button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(pause_button, &QPushButton::clicked, [=]() {
        // if (timer->isActive()) {
        //     timer->stop();
        //     pause_button->setText("Resume");
        // } else {
        //     timer->start(TickRate);
        //     pause_button->setText("Pause");
        // }
        if(controller->timer->isActive()){
            controller->stopSimulation();
            pause_button->setText("Resume");
        }
        else{
            controller->startSimulation();
            pause_button->setText("Pause simulation");
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


}

void PageSim::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // Start the simulation
    controller->startSimulation();
}

PageSim::~PageSim() {

}