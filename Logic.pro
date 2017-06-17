#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T23:12:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Logic
TEMPLATE = app


SOURCES += main.cpp \
    widget.cpp \
    gate.cpp \
    wire.cpp \
    graphwidget.cpp \
    pin.cpp \
    mainwindow.cpp \
    clock.cpp \
    userio.cpp \
    numericio.cpp \
    commands.cpp \
    multiplexer.cpp \
    flipflop.cpp \
    counter.cpp

HEADERS  += \
    widget.h \
    gate.h \
    wire.h \
    graphwidget.h \
    pin.h \
    mainwindow.h \
    clock.h \
    userio.h \
    numericio.h \
    commands.h \
    multiplexer.h \
    flipflop.h \
    counter.h

FORMS    += \
    widget.ui \
    mainwindow.ui
