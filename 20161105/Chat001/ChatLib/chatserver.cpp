#include "chatserver.h"

#include <QDataStream>
#include <QDebug>

ChatServer *ChatServer::m_instance = nullptr;

ChatServer *ChatServer::instance(){
    if(m_instance == nullptr){
        m_instance = new ChatServer;
    }
    return m_instance;
}

ChatServer::ChatServer(QObject *parent)
    : QObject(parent)
    , m_server(nullptr)
{
    m_server = new QTcpServer(this);
    connect( m_server, &QTcpServer::acceptError, this, &ChatServer::serverAcceptError);
    connect( m_server, &QTcpServer::newConnection, this, &ChatServer::serverNewConnection);
}

void ChatServer::listen(const QHostAddress &address, quint16 port)
{
    qDebug() << "listen( " << address << ", " << port << ")";
    m_server->listen(address, port);
}

void ChatServer::close()
{
    qDebug() << "close";
    m_server->close();
}

void ChatServer::serverAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "accept error: " + socketError;
}

void ChatServer::serverNewConnection()
{
    qDebug() << "new connection";
    while( m_server->hasPendingConnections() ){
        QTcpSocket *socket = m_server->nextPendingConnection();
        QString address = socket->peerAddress().toString();
        quint16 port = socket->peerPort();

        connect(socket, &QTcpSocket::readyRead, this, &ChatServer::socketReadyRead);
        connect(socket,&QTcpSocket::disconnected, this, &ChatServer::socketDisconnected);

        m_socketList << socket;
        emit connected(address, port);
    }
}

void ChatServer::socketReadyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    QString address = senderSocket->peerAddress().toString();
    quint16 port = senderSocket->peerPort();

    qDebug() << "socket ready read";
    qDebug() << "available bytes: " << senderSocket->bytesAvailable();

    while(senderSocket->bytesAvailable() > 0){
        QDataStream inStream(senderSocket);
        QString message;
        inStream >> message;
        emit messageReceived(address, port, message);
        for( auto socket: m_socketList ){
            QDataStream outStream(socket);
            outStream << message;
            socket->flush();
        }
    }
}

void ChatServer::socketDisconnected()
{
    qDebug() << "socket disconnected";
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    QString address = senderSocket->peerAddress().toString();
    quint16 port = senderSocket->peerPort();

    m_socketList.removeAll(senderSocket);
    emit disconnected(address, port);
}
