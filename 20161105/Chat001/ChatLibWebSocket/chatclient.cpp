#include "chatclient.h"

#include <QDataStream>
#include <QDebug>

ChatClient *ChatClient::m_instance = nullptr;

ChatClient *ChatClient::instance(){
    if(m_instance == nullptr){
        m_instance = new ChatClient;
    }
    return m_instance;
}

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
{
    m_socket = new QWebSocket();
    m_socket->setParent(this);

    connect(m_socket, &QWebSocket::connected, this, &ChatClient::socketConnected);
    connect(m_socket, &QWebSocket::disconnected, this, &ChatClient::socketDisconnected);
    connect<void(QWebSocket::*)(QAbstractSocket::SocketError)>(
                m_socket, &QWebSocket::error, this, &ChatClient::socketError);
    connect(m_socket, &QWebSocket::textMessageReceived,
            this, &ChatClient::socketTextMessageReceived);
}

void ChatClient::connectToHost(const QString &hostName, quint16 port)
{
    QString urlString = QString("ws://%1:%2/").arg(hostName).arg(port);
    qDebug() << "websocket connect to host " + urlString;
    m_socket->open(urlString);
}

void ChatClient::disconnectFromHost()
{
    qDebug() << "websocket disconnect from host.";
    m_socket->close();
}

void ChatClient::send(QString message)
{
    qDebug() <<"websocket send message: " + message;
    m_socket->sendTextMessage(message);
}

void ChatClient::socketConnected()
{
    qDebug() << "websocket connected.";
}

void ChatClient::socketDisconnected()
{
    qDebug() << "websocket disconnected.";
}

void ChatClient::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "websocket error: " << socketError;
}

void ChatClient::socketTextMessageReceived(const QString &message)
{
    qDebug() << "websocket text message received: " << message;

    emit received(message);
}
