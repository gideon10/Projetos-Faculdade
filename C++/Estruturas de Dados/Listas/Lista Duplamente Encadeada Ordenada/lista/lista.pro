QT += core
QT -= gui

CONFIG += c++11

TARGET = lista
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    noded.cpp \
    listadord.cpp \
    aluno.cpp

HEADERS += \
    noded.h \
    listadord.h \
    aluno.h
