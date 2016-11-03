#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QTextEdit>

#include "chatclient.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void connectClicked();
    void disconnectClicked();
    void clearClicked();
    void sendClicked();

private slots:
    void messageReceived(QString message);

private:
    QTextEdit *m_textLog;
    QTextEdit *m_textInput;
    QLineEdit *m_editHost;
    QLineEdit *m_editPort;

    ChatClient *m_chatClient;
};

#endif // MAINWIDGET_H
