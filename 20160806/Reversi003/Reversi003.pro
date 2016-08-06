#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T15:35:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reversi003
TEMPLATE = app


SOURCES += main.cpp\
        reversiwidget.cpp \
    cell.cpp \
    piece.cpp \
    game.cpp

HEADERS  += reversiwidget.h \
    cell.h \
    piece.h \
    game.h

TRANSLATIONS = Reversi003_ja.ts

RESOURCES += \
    reversi003.qrc

DISTFILES += \
    Reversi003_ja.ts
