
#include "PageMenu.hpp"
#include "MainWindow.hpp"
#include <QDebug>
PageMenu::PageMenu(QStackedWidget *stackedWidget, QWidget *parent) : QWidget(parent) {

    // start simulation button
    parent->resize(200, 190);



    QPushButton *button = new QPushButton("Start simulation", this);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);  

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(button);
    hLayout->addStretch(1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);


    connect(button, &QPushButton::clicked, [=]() {
        int simPageIndex = 1; 
        stackedWidget->setCurrentIndex(simPageIndex);
    });
}