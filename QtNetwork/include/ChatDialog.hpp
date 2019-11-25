#pragma once

#include "ChatDialog.ui"
#include "Client.hpp"

class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void showInformation();

private:
    Client client;
    QString myNickName;
    QTextTableFormat tableFormat;
};