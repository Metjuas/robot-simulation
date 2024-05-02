
// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0
#include "PageMenu.hpp"


/// @brief creates PageMenu, sets layout and button events
/// @param stacked_widget widget for page swapping
/// @param parent main window - parent
/// @param controller controller for passing data
PageMenu::PageMenu(QStackedWidget *stacked_widget, QWidget *parent, Controller *controller) : QWidget(parent), controller(controller) {
    this->controller = controller;
    this->setFixedSize(300,500);

    //create widgets
    create_button = new QPushButton("create map", this);
    QPushButton *select_button = new QPushButton("select map from file", this);
    start_button = new QPushButton("START", this);
    start_button->setObjectName("start_button");
    start_button->setStyleSheet("QPushButton{font-size:30px;}"
    "QPushButton:hover{font-size:34px;}");
    start_button->setFixedHeight(50);
    start_button->setEnabled(false);

    //add widgets and set layouts    
    QGridLayout *main_layout = new QGridLayout();
    QVBoxLayout *group_layout = new QVBoxLayout();
    group_layout->addWidget(create_button);
    group_layout->addWidget(select_button);
    main_layout->addLayout(group_layout, 0, 0,  Qt::AlignBottom);
    main_layout->addWidget(start_button, 1, 0,  Qt::AlignBottom);

    this->setLayout(main_layout);

    //button events
    connect(create_button, &QPushButton::clicked, [=]() {
        stacked_widget->setCurrentIndex(2);
        create_button->setText("edit");
        start_button->setEnabled(true);
    });

    connect(select_button, &QPushButton::clicked, [=]() {
        // stacked_widget->setCurrentIndex(3);
        QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open Map"), "./maps",
        tr("Map files (*.map)"));

    if (file_name.isEmpty())
        return;
    else 
    {
        int ret = this->controller->loadMap(file_name.toStdString());
        QMessageBox message_box;
        message_box.setIcon(QMessageBox::Warning);
        message_box.setWindowTitle("Caution");

        if(ret == 1)
        {
            message_box.setText("Cannot open map file!");
            message_box.exec();
        }
        else if(ret == 2)
        {
            message_box.setText("Invlid file format.");
            message_box.exec();
        }
        else
        {
            create_button->setText("edit");
            start_button->setEnabled(true);
        }
    }
    });

    connect(start_button, &QPushButton::clicked, [=]() {

        if(this->controller->map_width == 0 || this->controller->map_height == 0)
        {
            QMessageBox message_box;
            message_box.setIcon(QMessageBox::Warning);
            message_box.setWindowTitle("Caution");
            message_box.setText("Please create or select a map first.");
            message_box.exec();
            return;
        }
        parent->resize(this->controller->map_width,this->controller->map_height);
        stacked_widget->setCurrentIndex(1);
    });
}

/// @brief event when swapping to PageMenu
/// @param event 
void PageMenu::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    if(this->controller->map_width == 0 || this->controller->map_height == 0)
    {
        create_button->setText("create");
        start_button->setEnabled(false);
    }
}