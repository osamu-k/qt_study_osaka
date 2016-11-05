#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QWebSocket>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void connectClicked();
    void disconnectClicked();
    void sendClicked();

    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError socketError);
    void socketTextMessageReceived(const QString &mesage);



private:
    QTextEdit *m_editLog;
    QTextEdit *m_editInput;
    QLineEdit *m_editUrl;

    QWebSocket *m_socket;
};

#endif // MAINWIDGET_H
