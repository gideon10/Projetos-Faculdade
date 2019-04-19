QT += core
QT -= gui

CONFIG += c++11

TARGET = lista
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    aluno.cpp \
    listord.cpp

HEADERS += \
    node.h \
    aluno.h \
    listord.h
