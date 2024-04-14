#include "PageSim.hpp"
#include <QDebug>
#include <QDir>
#include "Sprite.hpp"


PageSim::PageSim(QWidget *parent) : QWidget(parent) {

    Sprite *sprite = new Sprite(":assets/RobotAlly.png", this, 100, 100);

    const int TickRate = 10;  //make this a cosntant

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        sprite->move(sprite->x() + 1, sprite->y());
    });
    timer->start(TickRate);

    QPushButton *button = new QPushButton("Pause simulation", this);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // toggle the timer on button click
    connect(button, &QPushButton::clicked, [=]() {
    if (timer->isActive()) {
        timer->stop();
        button->setText("Resume");
    } else {
        timer->start(TickRate);
        button->setText("Pause");
    }
    });
        
    // add the button to the layout
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(button);
    hLayout->addStretch(1);

    // add the layout to the page
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout); 
}