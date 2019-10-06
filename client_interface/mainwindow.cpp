/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** mainwindow.cpp
*/

#include "mainwindow.h"
#include <iostream>

mainWindow::mainWindow(): QWidget()
{
    setFixedSize(300, 150);
    _button = new QPushButton("Connection", this);
    _button->setFont(QFont("Comic Sans MS", 9));
    _button->setCursor(Qt::PointingHandCursor);
    _button->setIcon(QIcon("Green_circle.png"));
    _button->move(80, 100);

    _labelIp = new QLabel(QApplication::translate("windowlayout", "Server IP:"));
    _lineIp = new QLineEdit();
    _labelName = new QLabel(QApplication::translate("windowlayout", "Name:"));
    _lineName = new QLineEdit();

    _allLayout = new QFormLayout;
    _allLayout->addRow(_labelName, _lineName);
    _allLayout->addRow(_labelIp, _lineIp);
    
    // _allLayout = new QVBoxLayout();
    // _allLayout->addWidget(_layoutName);
    // _allLayout->addWidget(_layoutIp);

    this->setLayout(_allLayout);



    this->setWindowTitle("Babel");

    QObject::connect(_button, SIGNAL(clicked()), this, SLOT(takeIp()));

    // QObject::connect(_button, SIGNAL(clicked()), qApp, SLOT(quit()));

    // setFixedSize(300, 200);
    // _lcd = new QLCDNumber(this);
    // _lcd->setSegmentStyle(QLCDNumber::Flat);
    // _lcd->move(50, 20);
    // _slider = new QSlider(Qt::Horizontal, this);
    // _slider->setGeometry(10, 60, 150, 20);

    // QObject::connect(_slider, SIGNAL(valueChanged(int)), _lcd, SLOT(display(int)));

    // _sliderWindow = new QSlider(Qt::Horizontal, this);
    // _sliderWindow->setGeometry(10, 60, 150, 20);
    // _sliderWindow->move(50, 100);
    // _sliderWindow->setRange(300,600);
    // QObject::connect(_sliderWindow, SIGNAL(valueChanged(int)), this, SLOT(changerLargeur(int)));

}

mainWindow::~mainWindow()
{

}

void mainWindow::takeIp()
{
    std::cout << "adresse ip: " << _lineIp->text().toStdString() << std::endl;

}