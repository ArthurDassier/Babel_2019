/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** client main
*/

#define MAX 80

#include "Client.hpp"

int main(__attribute__((unused)) int argc, char **argv)
{
    cli::Client client;

    client.auth();
    client.run();
    return 0;
}
