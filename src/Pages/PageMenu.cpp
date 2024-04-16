
#include "PageMenu.hpp"

PageMenu::PageMenu(QStackedWidget *stackedWidget, QWidget *parent) : QWidget(parent) {

    parent->resize(300, 500);

    //create widgets
    QPushButton *create_button = new QPushButton("create map", this);
    QPushButton *select_button = new QPushButton("select map from file", this);
    QPushButton *start_button = new QPushButton("START", this);
    start_button->setFixedHeight(50);

    //add widgets and set layouts    
    QGridLayout *mainLayout = new QGridLayout();
    QVBoxLayout *groupLayout = new QVBoxLayout();
    groupLayout->addWidget(create_button);
    groupLayout->addWidget(select_button);
    mainLayout->addLayout(groupLayout, 0, 0,  Qt::AlignBottom);
    mainLayout->addWidget(start_button, 1, 0,  Qt::AlignBottom);

    this->setLayout(mainLayout);

    //button events
    connect(create_button, &QPushButton::clicked, [=]() {
        
        stackedWidget->setCurrentIndex(2);
    });

    connect(select_button, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(3);
    });

    connect(start_button, &QPushButton::clicked, [=]() {
        parent->resize(800,400);
        stackedWidget->setCurrentIndex(1);
    });
}