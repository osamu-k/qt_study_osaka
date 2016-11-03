#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QWebSocket>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    static ChatClient *instance();

    Q_INVOKABLE void connectToHost(const QString &hostName, quint16 port);
    Q_INVOKABLE void disconnectFromHost();
    Q_INVOKABLE void send(QString message);

signals:
    void received(QString message);

public slots:

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError socketError);
    void socketTextMessageReceived(const QString &mesage);

private:
    ChatClient(QObject *parent = 0);

    static ChatClient *m_instance;

    QWebSocket *m_socket;
};

#endif // CHATCLIENT_H
