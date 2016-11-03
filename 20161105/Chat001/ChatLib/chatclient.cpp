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
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::socketConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::socketDisconnected);
    connect<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(
                m_socket, &QTcpSocket::error, this, &ChatClient::socketError);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::socketReadyRead);
}

void ChatClient::connectToHost(const QString &hostName, quint16 port)
{
    qDebug() << "connect to host( " + hostName + ", " + port + ")";
    m_socket->connectToHost(hostName, port);
}

void ChatClient::disconnectFromHost()
{
    qDebug() << "disconnect from host.";
    m_socket->disconnectFromHost();
}

void ChatClient::send(QString message)
{
    qDebug() <<"send message: " + message;
    QDataStream outStream(m_socket);
    outStream << message;
    m_socket->flush();
}

void ChatClient::socketConnected()
{
    qDebug() << "socket connected.";
}

void ChatClient::socketDisconnected()
{
    qDebug() << "socket disconnected.";
}

void ChatClient::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "socket error: " << socketError;
}

void ChatClient::socketReadyRead()
{
    qDebug() << "socket ready read.";
    qDebug() << "available bytes: " << m_socket->bytesAvailable();

    while(m_socket->bytesAvailable()){
        QDataStream inStream(m_socket);
        QString message;
        inStream >> message;
        emit received(message);
    }
}
