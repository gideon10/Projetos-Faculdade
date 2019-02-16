QT += core
QT -= gui

CONFIG += c++11

TARGET = Stack
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Stack.cpp \
    Node.cpp \
    Aluno.cpp

HEADERS += \
    Stack.h \
    Node.h \
    Aluno.h
