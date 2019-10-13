/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** mainwindow.h
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class mainWindow : public QWidget
{
    Q_OBJECT

    public:
        mainWindow();
        ~mainWindow();

    public slots:
        void takeIp();
    
    private:
        QLabel *_labelName;
        QLineEdit *_lineName;
        QPushButton *_button;
        QLabel *_labelIp;
        QLineEdit *_lineIp;
        QFormLayout *_allLayout;
        // QLCDNumber *_lcd;
        // QSlider *_slider;
        // QSlider *_sliderWindow;
};

#endif

