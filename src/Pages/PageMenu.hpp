#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>



class PageMenu : public QWidget
{
    Q_OBJECT;
    public:
        PageMenu(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
        ~PageMenu();
    private:
        QStackedWidget *m_stackedWidget;
};
