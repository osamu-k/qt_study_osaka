#CONFIG += use_websocket

TEMPLATE = app

QT += qml quick
use_websocket{
    QT += websockets
}
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

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
