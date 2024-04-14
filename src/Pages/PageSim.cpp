#include "PageSim.hpp"

PageSim::PageSim(QWidget *parent) : QWidget(parent) {

    // i want just a label "simulation"

 
    QLabel *circle = new QLabel(this);
    circle->setGeometry(100, 100, 50, 50);
    circle->setStyleSheet("background-color: red; border-radius: 25px;");
    circle->show();
    

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        circle->move(circle->x() + 1, circle->y());
    });
    timer->start(10);
}
   