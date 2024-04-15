#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>

class Map
{    public:
        Map(QWidget *parent = nullptr);
        ~Map() = default;
    private:
        QWidget *m_parent;
};