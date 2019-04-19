QT += core
QT -= gui

CONFIG += c++11

TARGET = fila
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    queue.cpp \
    node.cpp \
    carta.cpp

HEADERS += \
    queue.h \
    node.h \
    carta.h
