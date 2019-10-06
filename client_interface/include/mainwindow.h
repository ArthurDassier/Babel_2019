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
        QPushButton *_button;
        QLabel *_labelName;
        QLineEdit *_lineName;
        QLabel *_labelIp;
        QLineEdit *_lineIp;
        QLabel *_labelPort;
        QLineEdit *_linePort;
        QFormLayout *_allLayout;
        // QLCDNumber *_lcd;
        // QSlider *_slider;
        // QSlider *_sliderWindow;
};

#endif

