#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T13:13:47
#
#-------------------------------------------------

QT       -= gui
QT       += network websockets

TARGET = ChatLibWebSocket
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    chatclient.cpp \
    chatserver.cpp

HEADERS += \
    chatclient.h \
    chatserver.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
