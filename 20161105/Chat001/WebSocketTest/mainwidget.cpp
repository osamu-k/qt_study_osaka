#include "mainwidget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_editLog(nullptr)
    , m_editInput(nullptr)
    , m_editUrl(nullptr)
    , m_socket(nullptr)
{
    m_editLog = new QTextEdit;
    m_editInput = new QTextEdit;
    m_editUrl = new QLineEdit;
    m_editUrl->setText("ws://echo.websocket.org");
    QPushButton *buttonConnect = new QPushButton("connect");
    QPushButton *buttonDisconnect = new QPushButton("disconnect");
    QPushButton *buttonSend = new QPushButton("send");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_editLog);
    layout->addWidget(m_editInput);
    layout->addWidget(m_editUrl);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonConnect);
    buttonLayout->addWidget(buttonDisconnect);
    buttonLayout->addWidget(buttonSend);

    layout->addLayout(buttonLayout);

    m_socket = new QWebSocket();
    m_socket->setParent(this);

    connect(buttonConnect, &QPushButton::clicked,
            this, &MainWidget::connectClicked);
    connect(buttonDisconnect, &QPushButton::clicked,
            this, &MainWidget::disconnectClicked);
    connect(buttonSend, &QPushButton::clicked,
            this, &MainWidget::sendClicked);

    connect(m_socket, &QWebSocket::connected, this, &MainWidget::socketConnected);
    connect(m_socket, &QWebSocket::disconnected, this, &MainWidget::socketDisconnected);
    connect<void(QWebSocket::*)(QAbstractSocket::SocketError)>(
                m_socket, &QWebSocket::error, this, &MainWidget::socketError);
    connect(m_socket, &QWebSocket::textMessageReceived,
            this, &MainWidget::socketTextMessageReceived);
}

MainWidget::~MainWidget()
{
}

void MainWidget::connectClicked()
{
    QString urlString = m_editUrl->text();
    qDebug() << "websocket connect to host " + urlString;
    m_socket->open(urlString);
}

void MainWidget::disconnectClicked()
{
    qDebug() << "websocket disconnect from host.";
    m_socket->close();
}

void MainWidget::sendClicked()
{
    QString message = m_editInput->toPlainText();
    qDebug() <<"websocket send message: " + message;
    m_socket->sendTextMessage(message);
}

void MainWidget::socketConnected()
{
    qDebug() << "websocket connected.";
}

void MainWidget::socketDisconnected()
{
    qDebug() << "websocket disconnected.";
}

void MainWidget::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "websocket error: " << socketError;
}

void MainWidget::socketTextMessageReceived(const QString &message)
{
    qDebug() << "websocket text message received: " << message;
}
