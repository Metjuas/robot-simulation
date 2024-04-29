
#include "PageCreate.hpp"


const int ROBOT_SPRITE_WIDTH = 64;
const int ROBOT_SPRITE_HEIGHT = 64;
const int BOX_SPRITE_HEIGHT = 64;
const int BOX_SPRITE_WIDTH = 64;
const int DELETE_SPRITE_SIZE = 64;

PageCreate:: ~PageCreate() {
    delete view;
}



/// @brief creates page for map creation, adds every widget and button
/// @param stacked_widget widget that handles page swapping
/// @param parent parent window 
/// @param controller controller for data passing
PageCreate::PageCreate(QStackedWidget *stacked_widget, QWidget *parent, Controller *controller)
 : QWidget(parent), stacked_widget(stacked_widget), controller(controller){
    this->controller = controller;
    this->current_cursor_state = cursor_state::IDLE;
    view = new CustomGraphicsView(&controller->scene, this);
    view->setRenderHint(QPainter::Antialiasing);


    //create widgets
    
    //button for robot
    QPushButton* robot_button = new QPushButton(this);
    QIcon icon(":assets/RobotAlly.png");
    robot_button->setIcon(icon);
    //settings size
    robot_button->setIconSize(QSize(30, 30));
    robot_button->setCheckable(true);
    
    //button for Box
    QPushButton* box_button = new QPushButton(this);
    QIcon b_icon(":assets/Box.png");
    box_button->setIcon(b_icon);
    //settings size
    box_button->setIconSize(QSize(30, 30));
    box_button->setCheckable(true);

    //button for Remove
    QPushButton* trash_button = new QPushButton(this);
    QIcon t_icon(":assets/remove.png");
    trash_button->setIcon(t_icon);
    //settings size
    trash_button->setIconSize(QSize(30, 30));
    trash_button->setCheckable(true);

    QLineEdit *map_name = new QLineEdit;
    map_name->setPlaceholderText("map name");
    QPushButton *ok_button = new QPushButton("Ok", this);
    QPushButton *save_button = new QPushButton("Save", this);


    setup_label = new QLabel();
    setup_label->setText("Robot setup");
    setup_label->setIndent(5);
    setup_label->setMargin(5);
    setup_label->setFixedHeight(35);
    robot_name = new QLineEdit;
    direction_num = new QSpinBox();
    direction_num->setPrefix("Direction:");
    direction_num->setMinimum(0);
    direction_num->setMaximum(360);
    distance_num = new QSpinBox();
    distance_num->setPrefix("Distance:");
    distance_num->setMinimum(30);
    distance_num->setMaximum(1000);
    direction_type = new QComboBox();
    rotation_num = new QSpinBox();
    rotation_num->setPrefix("Rotation angle: ");
    rotation_num->setMinimum(0);
    rotation_num->setMaximum(360);

    direction_type->addItem("left");
    direction_type->addItem("right");


    //add widgets and set layouts    
    tool_bar_layout = new QHBoxLayout();
    tool_bar_layout->addWidget(box_button);
    tool_bar_layout->addWidget(robot_button);  
    tool_bar_layout->addWidget(trash_button);
    tool_bar_layout->addWidget(map_name);
    tool_bar_layout->addWidget(ok_button);
    tool_bar_layout->addWidget(save_button);

    data_set_layout = new QVBoxLayout();
    data_set_layout->setAlignment(Qt::AlignCenter);
    data_set_layout->addWidget(setup_label);
    data_set_layout->addWidget(robot_name);
    data_set_layout->addWidget(direction_num);
    data_set_layout->addWidget(distance_num);
    data_set_layout->addWidget(rotation_num);
    data_set_layout->addWidget(direction_type);



    main_layout = new QGridLayout();


    this->setLayout(main_layout);

    //creating map 
    map = std::make_unique<Map>(controller, this);

    //clicking events
    connect(robot_button, &QPushButton::toggled, [this, robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            robot_button->setStyleSheet("background-color: #D3D3D3"); 
            box_button->setStyleSheet("");
            trash_button->setStyleSheet("");
            current_cursor_state = cursor_state::SPAWN_ROBOT;
            startRecordingClicks();
        } else {
            // reset color when button is unchecked
            robot_button->setStyleSheet("");
            stopRecordingClicks();
            current_cursor_state = cursor_state::IDLE;

        }
    });

    // click event for box button
    connect(box_button, &QPushButton::toggled, [this, robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            box_button->setStyleSheet("background-color: #D3D3D3");
            robot_button->setStyleSheet("");
            trash_button->setStyleSheet("");
            current_cursor_state = cursor_state::SPAWN_BOX;
            startRecordingClicks();
        } else {
            // reset color when button is unchecked
            box_button->setStyleSheet("");
            stopRecordingClicks();
            current_cursor_state = cursor_state::IDLE;
        }
    });

    // click event for trash button
    connect(trash_button, &QPushButton::toggled, [this, robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            trash_button->setStyleSheet("background-color: #D3D3D3"); 
            box_button->setStyleSheet("");
            robot_button->setStyleSheet("");
            current_cursor_state = cursor_state::REMOVE_ITEM;
            startRecordingClicks();
        } else {
            // reset color when button is unchecked
            trash_button->setStyleSheet("");
            stopRecordingClicks();
            current_cursor_state = cursor_state::IDLE;
        }
    });
        
    connect(view, &CustomGraphicsView::mouseClick, this, &PageCreate::handleMouseClick);

    connect(ok_button, &QPushButton::clicked, [=]() {
        controller->unselectRobot();
        //parent->resize(300,500);
        stacked_widget->setCurrentIndex(0);
    });

    connect(save_button, &QPushButton::clicked, [=]() {
        int ret = controller->saveMap(map_name->displayText().toUtf8().constData());

        QMessageBox message_box;
        message_box.setIcon(QMessageBox::Warning);
        message_box.setWindowTitle("Caution");

        if(ret == 1)
        {
            message_box.setText("Please insert map name.");
        }
        else if(ret == 2)
        {
            message_box.setText("Map with this name already exists!");
        }
        else if(ret == 0)
        {
            message_box.setIcon(QMessageBox::Information);
            message_box.setWindowTitle("Information");
            message_box.setText("Map created successfuly.");
        }

        message_box.exec();
    });

    
    //Robot setup events
    connect(robot_name, static_cast<void(QLineEdit::*)(const QString &)>(&QLineEdit::textChanged), [=](const QString &text) {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->setRobotName(text.toStdString());
        }
    });

    connect(direction_num, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value) {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->setRotation(value);
        }
    });

    connect(distance_num, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value) {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->setDistance(value);
        }
    });

    connect(rotation_num, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value) {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->setRobotRotation(value);
        }
    });
    
    connect(direction_type, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        if(controller->getSelectedRobot() != nullptr)
        {
            controller->getSelectedRobot()->setDirection(index==0?LEFT:RIGHT);
        }
    });

    robotSelectGUI(false);
    view->setMode(CustomGraphicsView::RecordClicks);
}


/// @brief handling mouse click - spawning entities
/// @param x x axis position of entity spawn
/// @param y y axis position of entity spawn
void PageCreate::handleMouseClick(int x, int y){
     if(current_cursor_state == cursor_state::SPAWN_ROBOT){
        //robot size

        int adjusted_x = std::max(ROBOT_SPRITE_WIDTH / 2, std::min(static_cast<int>(view->scene()->width()) - ROBOT_SPRITE_WIDTH / 2, x));
        int adjusted_y = std::max(ROBOT_SPRITE_HEIGHT / 2, std::min(static_cast<int>(view->scene()->height()) - ROBOT_SPRITE_HEIGHT / 2, y));

        if(controller->addRobot(adjusted_x, adjusted_y)){
            controller->spawnTopmostRobot();
            controller->selectRobot(adjusted_x, adjusted_y);
            robotSelectGUI(true);
        }

    }
    else if(current_cursor_state == cursor_state::SPAWN_BOX)
    {
        if(controller->addBox(x, y)){
            controller->spawnTopmostBox();
        }
    }
    else if(current_cursor_state == cursor_state::REMOVE_ITEM)
    {
        controller->removeItem(x, y);
        if(controller->getSelectedRobot() == nullptr)robotSelectGUI(false);
    }
    else
    {
        int ret = controller->selectRobot(x,y);
        if(ret == 1)
        {
            robotSelectGUI(true);
        }
        else if(ret == 2)
        {
            robotSelectGUI(false);
        }
    }
}

/// @brief handling recording clicks, changes mouse into sprite
void PageCreate::startRecordingClicks()
{
    if(current_cursor_state == cursor_state::SPAWN_ROBOT){
        QPixmap pixmap(":assets/RobotAlly.png");
        //adding transparency to the pixmap
        QPixmap transparent_pixmap(pixmap.size());
        transparent_pixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparent_pixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        //making the cursor robot
        QCursor cursor(transparent_pixmap.scaled(ROBOT_SPRITE_HEIGHT, ROBOT_SPRITE_WIDTH, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor); 
        //view->setMode(CustomGraphicsView::RecordClicks);
    }
    else if(current_cursor_state == cursor_state::SPAWN_BOX)
    {
        QPixmap pixmap(":assets/Box.png");
        //adding transparency to the pixmap
        QPixmap transparent_pixmap(pixmap.size());
        transparent_pixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparent_pixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        //making the cursor robot
        QCursor cursor(transparent_pixmap.scaled(BOX_SPRITE_HEIGHT, BOX_SPRITE_WIDTH, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor);
        //view->setMode(CustomGraphicsView::RecordClicks);        
    }
    else if(current_cursor_state == cursor_state::REMOVE_ITEM)
    {
        QPixmap pixmap(":assets/remove.png");
        //adding transparency to the pixmap
        QPixmap transparent_pixmap(pixmap.size());
        transparent_pixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparent_pixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        QCursor cursor(transparent_pixmap.scaled(DELETE_SPRITE_SIZE, DELETE_SPRITE_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor);
        //view->setMode(CustomGraphicsView::RecordClicks);    
    }
}


/// @brief stops recording clicks
void PageCreate::stopRecordingClicks()
{
    view->viewport()->setCursor(Qt::ArrowCursor);
}

/// @brief event when swapping to PageCreate - handles popup and resizing
/// @param event 
void PageCreate::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if (stacked_widget->currentIndex() == stacked_widget->indexOf(this)) {
        
        QDialog dialog(this);
        dialog.setWindowTitle("Set the size");
        QFormLayout form(&dialog);
        
        //dialog windows
        QSpinBox *spin_box_1 = new QSpinBox(&dialog);
        spin_box_1->setRange(250, 1600);
        spin_box_1->setValue(600);
        form.addRow("Height:", spin_box_1);

        QSpinBox *spin_box_2 = new QSpinBox(&dialog);
        spin_box_2->setRange(250, 1000);
        spin_box_2->setValue(600);
        form.addRow("Width:", spin_box_2);

        if(!(controller->map_height == 0 || controller->map_width ==0))
        {
            spin_box_1->setRange(controller->map_height, 900);
            spin_box_1->setValue(controller->map_height);
            spin_box_2->setRange(controller->map_width, 1500);
            spin_box_2->setValue(controller->map_width);
        }

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        //button function call
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

        // if the user accepts the dialog, it goes to the next page
        if (dialog.exec() == QDialog::Accepted) {
            if(controller){
                controller->map_height = spin_box_1->value();
                controller->map_width = spin_box_2->value();
                if(view){
                    view->setFixedSize(controller->map_width, controller->map_height);
                    controller->scene.setSceneRect(0, 0, controller->map_width, controller->map_height);
                    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                }
            }
        }
    }

    //add widgets to page
    main_layout->addLayout(tool_bar_layout, 1, 0,  Qt::AlignBottom);
    main_layout->addLayout(data_set_layout, 0, 1, 2, 1, Qt::AlignRight);
    main_layout->addWidget(view, 0, 0, 1, 1);
}

/// @brief hides every widget from page create
/// @param event 
void PageCreate::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    
    main_layout->removeItem(tool_bar_layout);
    main_layout->removeItem(data_set_layout);
    main_layout->removeWidget(view);
}

/// @brief robot selection handling
/// @param toggle 
void PageCreate::robotSelectGUI(bool toggle)
{
    if(toggle)
    {
        robot_name->setEnabled(true);
        direction_num->setEnabled(true);
        distance_num->setEnabled(true);
        direction_type->setEnabled(true);
        rotation_num->setEnabled(true);

        //load data to widgets
        Robot *robot = this->controller->getSelectedRobot();
        robot_name->setText(QString::fromStdString(robot->getRobotName()));
        direction_num->setValue(robot->getRotation());
        distance_num->setValue(robot->getDistance());
        rotation_num->setValue(robot->getRobotRotation());
        direction_type->setCurrentIndex(robot->getDirection()==LEFT?0:1);
    }
    else
    {
        robot_name->setEnabled(false);
        direction_num->setEnabled(false);
        distance_num->setEnabled(false);
        rotation_num->setEnabled(false);
        direction_type->setEnabled(false);
    }
}