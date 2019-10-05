/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** mainwindow.h
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>

class mainWindow : public QWidget
{
    Q_OBJECT

    public:
        mainWindow();
        ~mainWindow();

    public slots:
        void changerLargeur(int largeur);
    private:
        QPushButton *_button;
        QLCDNumber *_lcd;
        QSlider *_slider;
        QSlider *_sliderWindow;
};

#endif

