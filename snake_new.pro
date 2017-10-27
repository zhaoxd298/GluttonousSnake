#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T16:51:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = snake_new
TEMPLATE = app


SOURCES += main.cpp\
        welcome.cpp \
    gamewidget.cpp \
    optspace.cpp \
    gamespace.cpp

HEADERS  += welcome.h \
    gamewidget.h \
    optspace.h \
    gamespace.h

FORMS    += welcome.ui \
    gamewidget.ui \
    optspace.ui

RESOURCES += \
    source.qrc
