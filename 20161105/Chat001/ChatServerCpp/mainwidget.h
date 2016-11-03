#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QTextEdit>

#include "chatserver.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void startClicked();
    void stopClicked();
    void socketConnected(QString address, quint16 port);
    void socketDisconnected(QString address, quint16 port);
    void socketMessageReceived(QString address, quint16 port, QString message);

private:
    QTextEdit *m_textLog;
    QLineEdit *m_editPort;

    ChatServer *m_chatServer;
};

#endif // MAINWIDGET_H
