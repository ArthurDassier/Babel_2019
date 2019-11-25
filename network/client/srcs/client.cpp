/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** client
*/

#include <QtCore/QCoreApplication>

#include "QtClient.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpSocket s;
    s.doConnect();

    return a.exec();
}