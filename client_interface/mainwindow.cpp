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
    _labelPort = new QLabel(QApplication::translate("windowlayout", "Port:"));
    _linePort = new QLineEdit();

    _allLayout = new QFormLayout;
    _allLayout->addRow(_labelName, _lineName);
    _allLayout->addRow(_labelIp, _lineIp);
    _allLayout->addRow(_labelPort, _linePort);

    this->setLayout(_allLayout);
    this->setWindowTitle("Babel");
    QObject::connect(_button, SIGNAL(clicked()), this, SLOT(takeIp()));
}

mainWindow::~mainWindow()
{

}

void mainWindow::takeIp()
{
    std::cout << "name: " << _lineName->text().toStdString() << std::endl;
    std::cout << "adresse ip: " << _lineIp->text().toStdString() << std::endl;
    std::cout << "Port: " << _linePort->text().toStdString() << std::endl;
}