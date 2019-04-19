QT += core
QT -= gui

CONFIG += c++11

TARGET = lista
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    list.cpp \
    node.cpp \
    aluno.cpp

HEADERS += \
    list.h \
    node.h \
    aluno.h
