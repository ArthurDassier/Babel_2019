/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtInterface
*/

#pragma once

#include <QtWidgets>

class QtInterface : public QWidget
{
    Q_OBJECT
	public:
		QtInterface(QObject *parent);
		~QtInterface() = default;

    protected:
        QFormLayout *createFormLayout();
        QLabel      *createLabel(const std::string &text);
        QLineEdit   *createLineEdit();
        QPushButton *createPushButton(const QString &text, QWidget *parent = nullptr);
};