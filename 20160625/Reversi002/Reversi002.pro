#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T15:35:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reversi002
TEMPLATE = app


SOURCES += main.cpp\
        reversiwidget.cpp \
    cell.cpp \
    piece.cpp

HEADERS  += reversiwidget.h \
    cell.h \
    piece.h

TRANSLATIONS += Reversi002_ja.ts

DISTFILES += \
    Reversi002_ja.ts \
    Reversi002_ja.qm

RESOURCES += \
    Reversi002.qrc

