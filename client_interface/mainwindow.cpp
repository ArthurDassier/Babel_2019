/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** mainwindow.cpp
*/

#include "mainwindow.h"

mainWindow::mainWindow(): QWidget()
{
    // setFixedSize(300, 150);
    // _button = new QPushButton("SUICIDE", this);
    // _button->setFont(QFont("Comic Sans MS", 14));
    // _button->setCursor(Qt::PointingHandCursor);
    // _button->setIcon(QIcon("smile.png"));
    // _button->move(60, 50);

    // QObject::connect(_button, SIGNAL(clicked()), qApp, SLOT(quit()));

    setFixedSize(300, 200);
    _lcd = new QLCDNumber(this);
    _lcd->setSegmentStyle(QLCDNumber::Flat);
    _lcd->move(50, 20);
    _slider = new QSlider(Qt::Horizontal, this);
    _slider->setGeometry(10, 60, 150, 20);

    QObject::connect(_slider, SIGNAL(valueChanged(int)), _lcd, SLOT(display(int)));

    _sliderWindow = new QSlider(Qt::Horizontal, this);
    _sliderWindow->setGeometry(10, 60, 150, 20);
    _sliderWindow->move(50, 100);
    _sliderWindow->setRange(300,600);
    QObject::connect(_sliderWindow, SIGNAL(valueChanged(int)), this, SLOT(changerLargeur(int)));

}

mainWindow::~mainWindow()
{

}

void mainWindow::changerLargeur(int l)
{
    setFixedSize(l, 200);
}