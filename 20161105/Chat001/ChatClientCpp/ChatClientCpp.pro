#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T21:20:24
#
#-------------------------------------------------

#CONFIG += use_websocket

QT       += core gui network
use_websocket{
    QT += websockets
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClientCpp
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp

HEADERS  += mainwidget.h

use_websocket{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ChatLibWebSocket/release/ -lChatLibWebSocket
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ChatLibWebSocket/debug/ -lChatLibWebSocket
    else:unix: LIBS += -L$$OUT_PWD/../ChatLibWebSocket/ -lChatLibWebSocket

    INCLUDEPATH += $$PWD/../ChatLibWebSocket
    DEPENDPATH += $$PWD/../ChatLibWebSocket

    win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibWebSocket/release/libChatLibWebSocket.a
    else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibWebSocket/debug/libChatLibWebSocket.a
    else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibWebSocket/release/ChatLibWebSocket.lib
    else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibWebSocket/debug/ChatLibWebSocket.lib
    else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ChatLibWebSocket/libChatLibWebSocket.a
}
else{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ChatLib/release/ -lChatLib
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ChatLib/debug/ -lChatLib
    else:unix: LIBS += -L$$OUT_PWD/../ChatLib/ -lChatLib

    INCLUDEPATH += $$PWD/../ChatLib
    DEPENDPATH += $$PWD/../ChatLib

    win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/release/libChatLib.a
    else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/debug/libChatLib.a
    else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/release/ChatLib.lib
    else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/debug/ChatLib.lib
    else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/libChatLib.a
}
