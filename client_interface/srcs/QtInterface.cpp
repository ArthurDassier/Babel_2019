/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtInterface
*/

#include "QtInterface.hpp"

QtInterface::QtInterface(QObject *parent):
    QWidget()
{
}

QFormLayout *QtInterface::createFormLayout()
{
    return new QFormLayout();
}

QLabel *QtInterface::createLabel(const std::string &text = "")
{
    QLabel *label = new QLabel(
        QApplication::translate("windowlayout", text.c_str()));

    return label;
}

QLineEdit *QtInterface::createLineEdit()
{
    return new QLineEdit();
}

QPushButton *QtInterface::createPushButton(const QString &text, QWidget *parent)
{
    QPushButton *button = new QPushButton(text, parent);

    button->setCursor(Qt::PointingHandCursor);
    return button;
}