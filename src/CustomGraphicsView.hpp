#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

#include <utility>  



class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    enum Mode { Normal, RecordClicks };
    
    CustomGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent), mode(Normal){}

    void setMode(Mode mode) { this->mode = mode; }

    std::pair<int, int> getLastClickPosition() const { return lastClickPosition; }
    
signals:
    void mouseClick(int x, int y);
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Mode mode;
    std::pair<int,int> lastClickPosition;

};