
#include "PageCreate.hpp"
#include "MainWindow.hpp"
#include <QDebug>
PageCreate::PageCreate(QStackedWidget *stackedWidget, QWidget *parent) : QWidget(parent) {

    parent->resize(300, 500);

    //create widgets
    QPushButton *start_button = new QPushButton("create map", this);
    start_button->setFixedHeight(50);

    //add widgets and set layouts    
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(start_button, 1, 0,  Qt::AlignBottom);

    this->setLayout(mainLayout);

    connect(start_button, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(1);
    });
}