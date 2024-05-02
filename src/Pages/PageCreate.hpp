// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QtWidgets>
#include <QPixmap>
#include <QShowEvent>
#include <QHideEvent>

#include <memory>
#include <iostream>

#include "Sprite.hpp"
#include "Robot.hpp"

#include "Map.hpp"
#include "Controller.hpp"
#include "CustomGraphicsView.hpp"


class PageCreate : public QWidget
{
    Q_OBJECT;
    enum class cursor_state {
        IDLE,
        SPAWN_ROBOT,
        SPAWN_BOX,
        REMOVE_ITEM
    };

    public:
        PageCreate(QStackedWidget *stackedWidget, QWidget *parent = nullptr, Controller *controller = nullptr);
        ~PageCreate();
    protected:
        void showEvent(QShowEvent *event) override;
        void hideEvent(QHideEvent *event) override;
    private slots:
        void startRecordingClicks();
        void stopRecordingClicks();
        void handleMouseClick(int x, int y);
    private:
        void robotSelectGUI(bool toggle);

        QGridLayout *main_layout;
        QHBoxLayout *tool_bar_layout;
        QVBoxLayout *data_set_layout;
        CustomGraphicsView* view;

        QStackedWidget *stacked_widget;
        Controller *controller;
        
        std::unique_ptr<Map> map;
        cursor_state current_cursor_state;

        //Robot setup widgets
        QLabel *setup_label;
        QLineEdit *robot_name;
        QSpinBox *direction_num;
        QSpinBox *distance_num;
        QSpinBox *rotation_num;
        QComboBox *direction_type;
};
