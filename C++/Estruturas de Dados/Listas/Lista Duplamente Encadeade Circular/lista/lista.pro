QT += core
QT -= gui

CONFIG += c++11

TARGET = lista
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    listadcircular.cpp \
    noded.cpp \
    aluno.cpp

HEADERS += \
    listadcircular.h \
    noded.h \
    aluno.h
