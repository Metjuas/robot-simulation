// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0


#include "MainWindow.hpp"

/// @brief Creates the main window of the application, adds widgets to it and connects signals and slots
/// @param parent 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Robots");

    //set icon
    setWindowIcon(QIcon(":assets/RobotAlly.png"));

    controller = std::make_unique<Controller>();

    QStackedWidget *stacked_widget = new QStackedWidget(this);
    page_menu = std::make_unique<PageMenu>(stacked_widget, this, controller.get());
    page_create = std::make_unique<PageCreate>(stacked_widget, this, controller.get());
    page_sim = std::make_unique<PageSim>(stacked_widget, this, controller.get());

    stacked_widget->addWidget(page_menu.get());
    stacked_widget->addWidget(page_sim.get());
    stacked_widget->addWidget(page_create.get());
    setCentralWidget(stacked_widget);

    //set style
    setStyleSheet(
    "QPushButton:hover:!pressed{border: 2px solid black;font-size: 20px;background-color:rgb(236,233,216);}"
    "QLineEdit:hover,QLineEdit:focus{border: 2px solid black;}"
    "QSpinBox:hover,QSpinBox:focus{border: 2px solid black;}"
    "QComboBox:hover{border: 2px solid black;}"
    "QGraphicsView{border: 4px solid black;}"
    "QLabel{font-size: 28px;}"
    );

    QPixmap bkgnd(":/assets/main_background.png");
    bkgnd = bkgnd.scaled(300,500, Qt::KeepAspectRatio);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    connect(stacked_widget, &QStackedWidget::currentChanged, [=](int index) {
        if(index == 0)
        {
            this->setPalette(palette);
        }
        else
        {
            QPalette color_palette;
            color_palette.setColor(QPalette::Window, QColor(214, 218, 200));
            this->setPalette(color_palette);
        }
        adjustSize();
    });

}

