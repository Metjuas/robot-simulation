#pragma once

#include <QWidget>
#include <QLabel> 
#include <QPushButton> 
#include <QTimer>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

class PageSim : public QWidget
{
    Q_OBJECT;
    public:
    PageSim(QWidget *parent = nullptr);
    ~PageSim();
  
    private:
    QTimer *timer;
    QGraphicsScene scene;
    QGraphicsView view;

};