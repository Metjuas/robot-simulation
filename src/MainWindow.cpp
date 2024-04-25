
#include "MainWindow.hpp"

/// @brief Creates the main window of the application, adds widgets to it and connects signals and slots
/// @param parent 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Main window");
    controller = std::make_unique<Controller>();

    QStackedWidget *stacked_widget = new QStackedWidget(this);
    page_menu = std::make_unique<PageMenu>(stacked_widget, this, controller.get());
    page_create = std::make_unique<PageCreate>(stacked_widget, this, controller.get());
    page_sim = std::make_unique<PageSim>(stacked_widget, this, controller.get());

    stacked_widget->addWidget(page_menu.get());
    stacked_widget->addWidget(page_sim.get());
    stacked_widget->addWidget(page_create.get());
    setCentralWidget(stacked_widget);

    connect(stacked_widget, &QStackedWidget::currentChanged, [=](int) {
        adjustSize();
    });

}

