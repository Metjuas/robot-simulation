#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>


class PageCreate : public QWidget
{
    Q_OBJECT;
    public:
        PageCreate(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
        ~PageCreate() = default;
    private:
        QStackedWidget *m_stackedWidget;
};
