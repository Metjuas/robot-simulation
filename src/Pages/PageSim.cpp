#include "PageSim.hpp"

PageSim::PageSim(QWidget *parent, Controller *controller) : QWidget(parent), view(&controller->scene, nullptr) {

    view.setRenderHint(QPainter::Antialiasing);

    
    // Robot* robot = new Robot(100, 100);
    // robot->spawn(&controller->scene);

    const int TickRate = 2;

    timer = new QTimer(this);
    
    // connect(timer, &QTimer::timeout, [=]() {
    //     static int counter = 0;
    //     counter++;
    //     if (robot != nullptr) {
    //         if(counter % 5 == 0){
    //             robot->rotate();
    //         }
    //         robot->move();

    //     }
    // });

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
    timer->stop();
    delete timer;
}