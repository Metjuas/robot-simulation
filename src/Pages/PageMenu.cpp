
#include "PageMenu.hpp"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

PageMenu::PageMenu(QStackedWidget *stackedWidget, QWidget *parent, Controller *controller) : QWidget(parent), controller(controller) {
    this->controller = controller;
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
        // stackedWidget->setCurrentIndex(3);
        QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Map"), "./maps",
        tr("Map files (*.map)"));

    if (fileName.isEmpty())
        return;
    else 
    {
        int ret = this->controller->loadMap(fileName.toStdString());
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Caution");

        if(ret == 1)
        {
            msgBox.setText("Cannot open map file!");
            msgBox.exec();
        }
        else if(ret == 2)
        {
            msgBox.setText("Invlid file format.");
            msgBox.exec();
        }


        
    }
    });

    connect(start_button, &QPushButton::clicked, [=]() {

        if(this->controller->map_width == 0 || this->controller->map_height == 0)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Caution");
            msgBox.setText("Please create or select a map first.");
            msgBox.exec();
            return;
        }
        parent->resize(this->controller->map_width,this->controller->map_height);
        stackedWidget->setCurrentIndex(1);
    });
}