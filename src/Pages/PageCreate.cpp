
#include "PageCreate.hpp"
#include "MainWindow.hpp"


PageCreate::~PageCreate() {
}


PageCreate::PageCreate(QStackedWidget *stackedWidget, QWidget *parent, Controller *controller) : QWidget(parent), m_stackedWidget(stackedWidget) {

    parent->resize(300, 500);
    //i want a popup window that says "set the size of the map"

    this->controller = controller;

    //create widgets
    QLabel *Box_image = new QLabel("Box", this);
    QLabel *Robot_image = new QLabel("Robot", this);
    QLabel *Trash_image = new QLabel("Remove", this);
    QLineEdit *Map_name = new QLineEdit;
    QPushButton *ok_button = new QPushButton("Ok", this);
    QPushButton *save_button = new QPushButton("Save", this);

    QLineEdit *Robot_name = new QLineEdit;
    QDoubleSpinBox *direction_num = new QDoubleSpinBox();
    direction_num->setPrefix("Direction:");
    QDoubleSpinBox *distance_num = new QDoubleSpinBox();
    direction_num->setPrefix("Distance:");
    QComboBox *direction_type = new QComboBox();
    direction_type->addItem("left");
    direction_type->addItem("right");


    //add widgets and set layouts    
    QHBoxLayout *toolBarLayout = new QHBoxLayout();
    toolBarLayout->addWidget(Box_image);
    toolBarLayout->addWidget(Robot_image);
    toolBarLayout->addWidget(Trash_image);
    toolBarLayout->addWidget(Map_name);
    toolBarLayout->addWidget(ok_button);
    toolBarLayout->addWidget(save_button);

    QVBoxLayout *dataSetLayout = new QVBoxLayout();
    dataSetLayout->addWidget(Robot_name);
    dataSetLayout->addWidget(direction_num);
    dataSetLayout->addWidget(distance_num);
    dataSetLayout->addWidget(direction_type);


    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(toolBarLayout, 1, 0,  Qt::AlignBottom);
    mainLayout->addLayout(dataSetLayout, 0, 1, 2, 1, Qt::AlignRight);

    this->setLayout(mainLayout);

    connect(ok_button, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(1);
    });
}


void PageCreate::showEvent(QShowEvent *event) {
    if (m_stackedWidget->currentIndex() == m_stackedWidget->indexOf(this)) {
        
        QDialog dialog(this);
        dialog.setWindowTitle("Set the size");
        QFormLayout form(&dialog);
        
        //dialog windows
        QSpinBox *spinBox1 = new QSpinBox(&dialog);
        spinBox1->setRange(0, 1000);
        spinBox1->setValue(800);
        form.addRow("Height:", spinBox1);

        QSpinBox *spinBox2 = new QSpinBox(&dialog);
        spinBox2->setRange(0, 1000);
        spinBox2->setValue(400);
        form.addRow("Width:", spinBox2);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        //button function call
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // if the user accepts the dialog, it goes to the next page
        if (dialog.exec() == QDialog::Accepted) {
            controller->map_height = spinBox1->value();
            controller->map_width = spinBox2->value();
            resize( controller->map_width, controller->map_height);
        }    
        // in case the user cancels the dialog, it goes back to the main page
        else {
            m_stackedWidget->setCurrentIndex(0);
        }
    }

    QWidget::showEvent(event);
}