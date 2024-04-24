
#include "PageCreate.hpp"
#include <iostream>
#define SCENE_OFFSET 0


PageCreate:: ~PageCreate() {
    delete view;

}



PageCreate::PageCreate(QStackedWidget *stackedWidget, QWidget *parent, Controller *controller)
 : QWidget(parent), m_stackedWidget(stackedWidget), controller(controller){
    this->controller = controller;
    view = new CustomGraphicsView(&controller->scene, this);
    view->setRenderHint(QPainter::Antialiasing);


    //create widgets
    
    //button for robot
    QPushButton* Robot_button = new QPushButton(this);
    QIcon icon(":assets/RobotAlly.png");
    Robot_button->setIcon(icon);
    //settings size
    Robot_button->setIconSize(QSize(30, 30));
    Robot_button->setCheckable(true);
    
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

    QLineEdit *Map_name = new QLineEdit;
    QPushButton *ok_button = new QPushButton("Ok", this);
    QPushButton *save_button = new QPushButton("Save", this);

    Robot_name = new QLineEdit;
    direction_num = new QSpinBox();
    direction_num->setPrefix("Direction:");
    direction_num->setMinimum(0);
    direction_num->setMaximum(360);
    distance_num = new QSpinBox();
    distance_num->setPrefix("Distance:");
    direction_type = new QComboBox();

    rotation_num = new QSpinBox();
    rotation_num->setPrefix("Rotation angle: ");
    rotation_num->setMinimum(0);
    rotation_num->setMaximum(360);

    direction_type->addItem("left");
    direction_type->addItem("right");


    //add widgets and set layouts    
    toolBarLayout = new QHBoxLayout();
    toolBarLayout->addWidget(box_button);
    toolBarLayout->addWidget(Robot_button);  
    toolBarLayout->addWidget(trash_button);
    toolBarLayout->addWidget(Map_name);
    toolBarLayout->addWidget(ok_button);
    toolBarLayout->addWidget(save_button);

    dataSetLayout = new QVBoxLayout();
    dataSetLayout->addWidget(Robot_name);
    dataSetLayout->addWidget(direction_num);
    dataSetLayout->addWidget(distance_num);
    dataSetLayout->addWidget(rotation_num);

    dataSetLayout->addWidget(direction_type);


    mainLayout = new QGridLayout();


    this->setLayout(mainLayout);

    //creating map 
    map = std::make_unique<Map>(controller, this);

    //clicking events
    connect(Robot_button, &QPushButton::toggled, [this, Robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            Robot_button->setStyleSheet("background-color: #D3D3D3"); 
            box_button->setStyleSheet("");
            trash_button->setStyleSheet("");
            current_cursor_state = cursor_state::SPAWN_ROBOT;
            startRecordingClicks();
        } else {
            // reset color when button is unchecked
            Robot_button->setStyleSheet("");
            stopRecordingClicks();
            current_cursor_state = cursor_state::IDLE;

        }
    });

    connect(box_button, &QPushButton::toggled, [this, Robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            box_button->setStyleSheet("background-color: #D3D3D3");
            Robot_button->setStyleSheet("");
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

    connect(trash_button, &QPushButton::toggled, [this, Robot_button, box_button, trash_button](bool checked) {
        if (checked) {
            // change color to light gray when button is checked
            trash_button->setStyleSheet("background-color: #D3D3D3"); 
            box_button->setStyleSheet("");
            Robot_button->setStyleSheet("");
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
        stackedWidget->setCurrentIndex(0);
    });

    connect(save_button, &QPushButton::clicked, [=]() {
        int ret = controller->saveMap(Map_name->displayText().toUtf8().constData());

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Caution");

        if(ret == 1)
        {
            msgBox.setText("Please insert map name.");
        }
        else if(ret == 2)
        {
            msgBox.setText("Map with this name already exists!");
        }
        else if(ret == 0)
        {
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("Information");
            msgBox.setText("Map created successfuly.");
        }

        msgBox.exec();
    });

    
    //Robot setup events
    connect(Robot_name, static_cast<void(QLineEdit::*)(const QString &)>(&QLineEdit::textChanged), [=](const QString &text) {
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



void PageCreate::handleMouseClick(int x, int y){
    std::cout << "Mouse click at: " << x << ", " << y << std::endl;
     if(current_cursor_state == cursor_state::SPAWN_ROBOT){
        //robot size
        int robotWidth = 64; 
        int robotHeight = 64;

        int adjustedX = std::max(robotWidth / 2, std::min(static_cast<int>(view->scene()->width()) - robotWidth / 2, x));
        int adjustedY = std::max(robotHeight / 2, std::min(static_cast<int>(view->scene()->height()) - robotHeight / 2, y));

        if(controller->addRobot(adjustedX, adjustedY)){
            controller->spawnTopmostRobot();
            controller->selectRobot(adjustedX, adjustedY);
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

void PageCreate::startRecordingClicks()
{
    if(current_cursor_state == cursor_state::SPAWN_ROBOT){
        QPixmap pixmap(":assets/RobotAlly.png");
        //adding transparency to the pixmap
        QPixmap transparentPixmap(pixmap.size());
        transparentPixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparentPixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        //making the cursor robot
        QCursor cursor(transparentPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor); 
        //view->setMode(CustomGraphicsView::RecordClicks);
    }
    else if(current_cursor_state == cursor_state::SPAWN_BOX)
    {
        QPixmap pixmap(":assets/Box.png");
        //adding transparency to the pixmap
        QPixmap transparentPixmap(pixmap.size());
        transparentPixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparentPixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        //making the cursor robot
        QCursor cursor(transparentPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor);
        //view->setMode(CustomGraphicsView::RecordClicks);        
    }
    else if(current_cursor_state == cursor_state::REMOVE_ITEM)
    {
        QPixmap pixmap(":assets/remove.png");
        //adding transparency to the pixmap
        QPixmap transparentPixmap(pixmap.size());
        transparentPixmap.fill(Qt::transparent); 
        //setting the opacity of the pixmap
        QPainter painter(&transparentPixmap);
        painter.setOpacity(0.5); 
        painter.drawPixmap(0, 0, pixmap); 
        painter.end();
        //making the cursor robot
        QCursor cursor(transparentPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation), -1, -1);
        view->viewport()->setCursor(cursor);
        //view->setMode(CustomGraphicsView::RecordClicks);    
    }
}


void PageCreate::stopRecordingClicks()
{
    view->viewport()->setCursor(Qt::ArrowCursor);
    //view->setMode(CustomGraphicsView::Normal);
}

void PageCreate::showEvent(QShowEvent *event) {
    if (m_stackedWidget->currentIndex() == m_stackedWidget->indexOf(this)) {
        
        QDialog dialog(this);
        dialog.setWindowTitle("Set the size");
        QFormLayout form(&dialog);
        
        //dialog windows
        QSpinBox *spinBox1 = new QSpinBox(&dialog);
        spinBox1->setRange(0, 1000);
        spinBox1->setValue(600);
        form.addRow("Height:", spinBox1);

        QSpinBox *spinBox2 = new QSpinBox(&dialog);
        spinBox2->setRange(0, 1000);
        spinBox2->setValue(600);
        form.addRow("Width:", spinBox2);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        //button function call
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // if the user accepts the dialog, it goes to the next page
       if (dialog.exec() == QDialog::Accepted) {
            if(controller){
                controller->map_height = spinBox1->value();
                controller->map_width = spinBox2->value();
                if(view){
                    view->setFixedSize(controller->map_width, controller->map_height);
                    controller->scene.setSceneRect(0, 0, controller->map_width, controller->map_height);
                    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                }
            }
        }
        // in case the user cancels the dialog, it goes back to the main page
        else {
            m_stackedWidget->setCurrentIndex(0);
        }
    }

    QWidget::showEvent(event);

    //add widgets to page
    mainLayout->addLayout(toolBarLayout, 1, 0,  Qt::AlignBottom);
    mainLayout->addLayout(dataSetLayout, 0, 1, 2, 1, Qt::AlignRight);
    mainLayout->addWidget(view, 0, 0, 1, 1);
}

void PageCreate::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    
    mainLayout->removeItem(toolBarLayout);
    mainLayout->removeItem(dataSetLayout);
    mainLayout->removeWidget(view);
}

void PageCreate::robotSelectGUI(bool toggle)
{
    if(toggle)
    {
        Robot_name->setEnabled(true);
        direction_num->setEnabled(true);
        distance_num->setEnabled(true);
        direction_type->setEnabled(true);
        rotation_num->setEnabled(true);

        //load data to widgets
        Robot *robot = this->controller->getSelectedRobot();
        Robot_name->setText(QString::fromStdString(robot->getRobotName()));
        direction_num->setValue(robot->getRotation());
        distance_num->setValue(robot->getDistance());
        rotation_num->setValue(robot->getRobotRotation());
        direction_type->setCurrentIndex(robot->getDirection()==LEFT?0:1);


    }
    else
    {
        Robot_name->setEnabled(false);
        direction_num->setEnabled(false);
        distance_num->setEnabled(false);
        rotation_num->setEnabled(false);
        direction_type->setEnabled(false);
    }
}