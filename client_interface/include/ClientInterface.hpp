/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientInterface
*/

#pragma once

#include <QtWidgets>

#include "QtInterface.hpp"

class ClientInterface : public QtInterface
{
	public:
        ClientInterface(QObject *parent);
        ~ClientInterface() = default;

        QFormLayout *callLayout();
        QFormLayout *commandLayout();
        QFormLayout *responseLayout();
        
        QPushButton *callButton();
        QPushButton *commandButton();

        QGridLayout *renderInterface();

        void        setResponse(const QString &text);

        QLineEdit   *getAddress() const noexcept;
        QPushButton *getCallButton() const noexcept;
        QLineEdit   *getCommand() const noexcept;
        QPushButton *getCommandButton() const noexcept;
        QLineEdit   *getPort() const noexcept;
        QLabel      *getResponse() const noexcept;

    protected:
    private:
        QLabel      *_response;
        QLineEdit   *_address;
        QLineEdit   *_command;
        QLineEdit   *_port;
        QPushButton *_callButton;
        QPushButton *_commandButton;
};