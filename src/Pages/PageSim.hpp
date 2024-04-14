#pragma once

#include <QWidget>
#include <QLabel> 
#include <QPushButton> 
#include <QTimer>
#include <QVBoxLayout>


class PageSim : public QWidget
{
    Q_OBJECT;
    public:
    PageSim(QWidget *parent = nullptr);
    ~PageSim() = default;
};