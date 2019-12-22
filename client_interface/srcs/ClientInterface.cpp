/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientInterface
*/

#include "ClientInterface.hpp"

ClientInterface::ClientInterface(QObject *parent):
    QtInterface(parent),
    _address(nullptr),
    _command(nullptr),
    _port(nullptr)
{
}

QFormLayout *ClientInterface::callLayout()
{
    QFormLayout *layout = createFormLayout();
    QLabel *addressLabel = createLabel("Address:");
    QLabel *portLabel = createLabel("Port:");
    _address = createLineEdit();
    _port = createLineEdit();

    layout->addRow(addressLabel, _address);
    layout->addRow(portLabel, _port);
    return layout;
}

QFormLayout *ClientInterface::commandLayout()
{
    QFormLayout *layout = createFormLayout();
    QLabel *commandLabel = createLabel("Command:");
    _command = createLineEdit();

    layout->addRow(commandLabel, _command);
    return layout;
}

QFormLayout *ClientInterface::responseLayout()
{
    QFormLayout *layout = createFormLayout();
    QLabel *response = createLabel("Response:");
    _response = createLabel("Your answer will appear here");

    layout->addRow(response, _response);
    return layout;
}

QPushButton *ClientInterface::callButton() {
    _callButton = createPushButton("Call", this);
    _callButton->setIcon(QIcon("Green_circle.png"));

    return _callButton;
}

QPushButton *ClientInterface::commandButton() {
    _commandButton = createPushButton("Send to server", this);

    return _commandButton;
}

QGridLayout *ClientInterface::renderInterface()
{
    QGridLayout *gridLayout = new QGridLayout();

    gridLayout->addLayout(callLayout(), 1, 1);
    gridLayout->addLayout(commandLayout(), 1, 0);
    gridLayout->addLayout(responseLayout(), 0, 0, 2, 2);
    gridLayout->addWidget(callButton(), 2, 1);
    gridLayout->addWidget(commandButton(), 2, 0);
    return gridLayout;
}

void ClientInterface::setResponse(const QString &text)
{
    _response->setText(text);
}

QLineEdit *ClientInterface::getAddress() const noexcept {
    return _address;
}

QPushButton *ClientInterface::getCallButton() const noexcept
{
    return _callButton;
}

QLineEdit *ClientInterface::getCommand() const noexcept {
    return _command;
}

QPushButton *ClientInterface::getCommandButton() const noexcept
{
    return _commandButton;
}

QLineEdit *ClientInterface::getPort() const noexcept
{
    return _port;
}

QLabel *ClientInterface::getResponse() const noexcept
{
    return _response;
}