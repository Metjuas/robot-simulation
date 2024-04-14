
#include "PageMenu.hpp"


PageMenu::PageMenu(QStackedWidget *stackedWidget, QWidget *parent) : QWidget(parent) {
    QPushButton *button = new QPushButton("Start simulation", this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    this->setLayout(layout);

    connect(button, &QPushButton::clicked, [=]() {
        int simPageIndex = 1;  // Index of the simulation page
        stackedWidget->setCurrentIndex(simPageIndex);
    });
}