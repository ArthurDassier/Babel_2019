/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** client
*/

#include <QtCore/QCoreApplication>

#include "Client.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client s(argv[1], std::atoi(argv[2]));

    s.SaySomething();
    return a.exec();
}