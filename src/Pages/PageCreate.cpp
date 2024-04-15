
#include "PageCreate.hpp"
#include "MainWindow.hpp"

PageCreate::PageCreate(QStackedWidget *stackedWidget, QWidget *parent) : QWidget(parent), m_stackedWidget(stackedWidget) {

    parent->resize(300, 500);
    //i want a popup window that says "set the size of the map"



    //create widgets
    QPushButton *start_button = new QPushButton("create map", this);
    start_button->setFixedHeight(50);

    QPushButton *save_button = new QPushButton("Save", this);
    save_button->setFixedHeight(50);

    //add widgets and set layouts    

    
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(start_button, 1, 0,  Qt::AlignBottom);
    mainLayout->addWidget(save_button, 1, 1,  Qt::AlignBottom);

    this->setLayout(mainLayout);

    connect(start_button, &QPushButton::clicked, [=]() {
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
        spinBox1->setRange(0, 100);
        spinBox1->setValue(25);
        form.addRow("Height:", spinBox1);

        QSpinBox *spinBox2 = new QSpinBox(&dialog);
        spinBox2->setRange(0, 100);
        spinBox2->setValue(25);
        form.addRow("Width:", spinBox2);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        //button function call
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // if the user accepts the dialog, it goes to the next page
        if (dialog.exec() == QDialog::Accepted) {
            int height = spinBox1->value();
            int width = spinBox2->value();
        }    
        // in case the user cancels the dialog, it goes back to the main page
        else {
            m_stackedWidget->setCurrentIndex(0);
        }
    }

    QWidget::showEvent(event);
}