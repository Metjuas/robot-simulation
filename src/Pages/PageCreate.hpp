#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QtWidgets>


class PageCreate : public QWidget
{
    Q_OBJECT;
    public:
        PageCreate(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
        ~PageCreate() = default;
    protected:
        void showEvent(QShowEvent *event) override;
    private:
        QStackedWidget *m_stackedWidget;
};
