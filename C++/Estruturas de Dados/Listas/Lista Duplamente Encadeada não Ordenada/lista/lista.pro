QT += core
QT -= gui

CONFIG += c++11

TARGET = lista
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    listad.cpp \
    noded.cpp \
    aluno.cpp

HEADERS += \
    listad.h \
    noded.h \
    aluno.h
