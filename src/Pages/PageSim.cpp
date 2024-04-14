#include "PageSim.hpp"
#include <QDebug>
#include <QDir>
#include "Sprite.hpp"
#include "Robot.hpp"
#include <iostream>
#include <QPointer>

PageSim::PageSim(QWidget *parent) : QWidget(parent), view(&scene, this) {
    view.setRenderHint(QPainter::Antialiasing);
    view.setFixedSize(800, 600);

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

    QPushButton *button = new QPushButton("Pause simulation", this);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(button, &QPushButton::clicked, [=]() {
        if (timer->isActive()) {
            timer->stop();
            button->setText("Resume");
        } else {
            timer->start(TickRate);
            button->setText("Pause");
        }
    });

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(button);
    hLayout->addStretch(1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(&view);  // Add the QGraphicsView to the layout
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);
}

PageSim::~PageSim() {
}