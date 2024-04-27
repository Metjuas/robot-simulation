
#include "MainWindow.hpp"
#include <QFont>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //set font
    int font_id = QFontDatabase::addApplicationFont(":/assets/PixelifySans.ttf");
    QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont font(family);
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    MainWindow mainWindow;
    mainWindow.show();
    
    
    return app.exec();
}
