#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>


class PageMenu : public QWidget
{
    Q_OBJECT;
    public:
        PageMenu(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
    private:
        QStackedWidget *m_stackedWidget;
};
