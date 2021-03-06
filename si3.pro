#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T22:33:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = si3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamewindowpve.cpp \
    node.cpp \
    utility.cpp \
    gamewindowpvp.cpp \
    gamewindow.cpp \
    gamewindoweve.cpp

HEADERS += \
        mainwindow.h \
    gamewindowpve.h \
    node.h \
    utility.h \
    gamewindowpvp.h \
    gamewindow.h \
    gamewindoweve.h

FORMS += \
        mainwindow.ui \
    gamewindowpve.ui \
    gamewindowpvp.ui \
    gamewindoweve.ui
