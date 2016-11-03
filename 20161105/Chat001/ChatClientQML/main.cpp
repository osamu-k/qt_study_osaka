#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "chatclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("chatClient",
                                             ChatClient::instance());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
