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
    m_server = new QWebSocketServer("ChatServerQML",
                                    QWebSocketServer::NonSecureMode,
                                    this);
    connect( m_server, &QWebSocketServer::acceptError, this, &ChatServer::serverAcceptError);
    connect( m_server, &QWebSocketServer::newConnection, this, &ChatServer::serverNewConnection);
}

void ChatServer::listen(const QHostAddress &address, quint16 port)
{
    qDebug() << "websocket listen( " << address << ", " << port << ")";
    m_server->listen(address, port);
}

void ChatServer::close()
{
    qDebug() << "websocket close";
    m_server->close();
}

void ChatServer::serverAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "websocket accept error: " + socketError;
}

void ChatServer::serverNewConnection()
{
    qDebug() << "websocket new connection";
    while( m_server->hasPendingConnections() ){
        QWebSocket *socket = m_server->nextPendingConnection();
        connect(socket, &QWebSocket::textMessageReceived, this, &ChatServer::socketTextMessageReceived);
        connect(socket,&QWebSocket::disconnected, this, &ChatServer::socketDisconnected);
        m_socketList << socket;
        QString address = socket->peerAddress().toString();
        quint16 port = socket->peerPort();
        emit connected(address, port);
    }
}

void ChatServer::socketTextMessageReceived(const QString &message)
{
    qDebug() << "websocket text message received: " + message;
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    QString address = senderSocket->peerAddress().toString();
    quint16 port = senderSocket->peerPort();
    emit messageReceived(address, port, message);
    for( auto socket: m_socketList ){
        socket->sendTextMessage(message);
    }
}

void ChatServer::socketDisconnected()
{
    qDebug() << "websocket disconnected";
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    m_socketList.removeAll(senderSocket);
    QString address = senderSocket->peerAddress().toString();
    quint16 port = senderSocket->peerPort();
    emit disconnected(address, port);
}
