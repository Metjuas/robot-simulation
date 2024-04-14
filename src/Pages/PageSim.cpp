#include "PageSim.hpp"
#include <QDebug>
#include <QDir>
#include "Sprite.hpp"
#include "Robot.hpp"
#include <iostream>
#include <QPointer>

PageSim::PageSim(QWidget *parent) : QWidget(parent), view(&scene, this) {

    view.setRenderHint(QPainter::Antialiasing);

    QPointer<Robot> robot = new Robot(100, 100);
    robot->spawn(&scene);

    const int TickRate = 10;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        if (!robot.isNull()) {
            robot->move();
            // robot->rotate();
        }
    });

    timer->start(TickRate);

    QPushButton *pause_button = new QPushButton("Pause simulation", this);
    pause_button->setFixedHeight(50);
    QPushButton *menu_button = new QPushButton("Menu", this);
    menu_button->setFixedHeight(50);
    QPushButton *go_button = new QPushButton("Go/Stop", this);
    QPushButton *left_button = new QPushButton("<-", this);
    QPushButton *right_button = new QPushButton("->", this);
    //button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(pause_button, &QPushButton::clicked, [=]() {
        if (timer->isActive()) {
            timer->stop();
            pause_button->setText("Resume");
        } else {
            timer->start(TickRate);
            pause_button->setText("Pause");
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
    vLayout->addWidget(&view);
    vLayout->addLayout(gridLayout);

    this->setLayout(vLayout);
}

PageSim::~PageSim() {
}