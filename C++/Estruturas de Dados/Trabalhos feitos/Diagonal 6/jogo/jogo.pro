QT += core
QT -= gui

CONFIG += c++11

TARGET = jogo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ficha.cpp \
    stack.cpp \
    queue.cpp \
    node.cpp

HEADERS += \
    ficha.h \
    stack.h \
    queue.h \
    node.h
